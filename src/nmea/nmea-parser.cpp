// #include <iostream> // For debugging
#include <stdexcept>
#include <regex>

#include "nmea-parser.h"

namespace GPS::NMEA
{
  bool isSupportedFormat(std::string characterFormat)
  {
      //Regex to determine whether the parameter is the three-character code for sentence format
      const std::regex reg("(GLL|GGA|RMC)");
      return std::regex_match (characterFormat, reg);
  }

  bool hasValidSentenceStructure(std::string sentence)
  {
      //Regex to determine whether the sentence conforms to the structure of NMEA sentence
      std::regex expression("(\\$GP)([A-Z]){3},(\\w|[-]|[.]|[,]){0,}\\*[[:xdigit:]]{2}");
      return std::regex_match(sentence, expression);
  }

  bool checksumMatches(std::string sentence)
  {
      int baseHex = 16;
      int endPoint = sentence.length() - 2;

      //Obtains checksum provided from sentence
      std::string subString = sentence.substr(endPoint);
      int hexValues = std::stoul(subString, nullptr, baseHex);

      //Calculation of new bitwise checksum, via XOR
      int checksum = 0;
      for(int i = 1; i < endPoint - 1; i++) {
          checksum ^= sentence[i];
      }
      return (checksum == hexValues);
  }

  SentenceData parseSentence(std::string sentence)
  {
      //Creation of string to take sentece format, with: starting position 3 and length of 3 characters
      std::string sFormat = sentence.substr(3, 3);

      //Creation of vector for Data Fields
      std::vector<std::string> dataFields;
      std::string format = "";

      //Loop that pushes fields into vector value
      //Finds occurance of `,` and end of Data Fields
      for (unsigned int i =7 ;i <sentence.length() - 2; i++) {
          char contents = sentence[i];
          if((contents == ',')|| (contents == '*')){
              dataFields.push_back(format);
              format = "";
          }
          else {
              format = format + contents;
          }
      }
      return {sFormat, dataFields};
  }

  bool hasCorrectNumberOfFields(SentenceData sentenceData)
  {
      int fieldAmount = sentenceData.dataFields.size();

      if (sentenceData.format == "GLL" && fieldAmount == 5){
          return true;
      }
      else if (sentenceData.format == "GGA" && fieldAmount == 14) {
          return true;
      }
      else if (sentenceData.format == "RMC" && fieldAmount ==11) {
          return true;
      }
      else {
          return false;
      }
  }

  void sentenceBearing (std::string northSouth, std::string eastWest)
  {
      if (northSouth.size() != 1) {
            throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + northSouth + ". Bearings must be a single character.");
      }
          else if (eastWest.size() != 1) {
              throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + eastWest + ". Bearings must be a single character.");
          }
  }


  Position positionFromSentenceData(SentenceData d)
  {
      std::string latitude, longitude, northSouth, eastWest, elevation;
      Position p = Position(0,0,0);

      if (d.format == "GLL" && d.dataFields.size() == 5)
      {
          latitude = d.dataFields[0];
          longitude = d.dataFields[2];
          northSouth = d.dataFields[1];
          eastWest = d.dataFields[3];
          elevation = "0";
      }

      else if (d.format == "GGA" && d.dataFields.size() == 14) {
          latitude = d.dataFields[1];
          longitude = d.dataFields[3];
          northSouth = d.dataFields[2];
          eastWest = d.dataFields[4];
          elevation = d.dataFields[8];
      }
      else if (d.format == "RMC" && d.dataFields.size() ==11) {
          latitude = d.dataFields[2];
          longitude = d.dataFields[4];
          northSouth = d.dataFields[3];
          eastWest = d.dataFields[5];
          elevation = "0";
      }
      else {
          throw std::domain_error(std::string("Ill-formed bearing in sentence field: "));
      }

      sentenceBearing(northSouth, eastWest);

      try {
          p = Position(latitude,northSouth[0],longitude,eastWest[0],elevation);
      } catch (const std::invalid_argument& e) {
          throw std::domain_error(std::string("Ill-formed GLL sentence field: ") + e.what());
      }
    return p;
  }

  std::vector<Position> readSentences(std::istream & stream)
  {
      std::vector<Position> vector;

      while (true) {
          std::string validData;
          stream >> validData;
          if (stream.eof()) {
              break;
          }
          if (!validData.length()) {
              continue;
          }

          //Checks line is valid by meeting five conditons
          try {
              if(!hasValidSentenceStructure(validData)) {
                  throw std::invalid_argument("Parameter doesn't conform to the structure of a NMEA sentence");
              }
              SentenceData sentence (parseSentence(validData));

              if((isSupportedFormat(sentence.format))&&(hasValidSentenceStructure(validData))&&(checksumMatches(validData))) {
                  vector.push_back(positionFromSentenceData(sentence));
              }
          } catch (const std::exception& ) {
          }
      }
      return vector;
  }
}
