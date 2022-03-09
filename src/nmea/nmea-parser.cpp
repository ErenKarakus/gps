// #include <iostream> // For debugging
#include <stdexcept>
#include <regex>

#include "nmea-parser.h"

namespace GPS::NMEA
{
  bool isSupportedFormat(std::string characterFormat)
  {
      // Stub definition, needs implementing
      const std::regex reg("(GLL|GGA|RMC)");
      return std::regex_match (characterFormat, reg);
  }

  bool hasValidSentenceStructure(std::string s)
  {
      std::regex expression("(\\$GP)([A-Z]){3},(\\w|[.]|[,]){0,}\\*[[:xdigit:]]{2}");
      return std::regex_match(s, expression);
  }

  bool checksumMatches(std::string s)
  {
      // Stub definition, needs implementing
      int baseHex = 16;
      int endPoint = s.length() - 2;

      std::string subString = s.substr(endPoint);
      int hexValues = std::stoul(subString, nullptr, baseHex);

      int checksum = 0;
      for(int i = 1; i < endPoint - 1; i++) {
          checksum ^= s[i];
      }

      return (checksum == hexValues);
  }

  SentenceData parseSentence(std::string s)
  {
      // Stub definition, needs implementing
      std::string format = s.substr(3, 3);

      std::vector<std::string> field;
      std::string data = "";

      for (int i =7 ;i <s.length() - 2; i++) {
          char contents = s[i];
          if((contents == ',')|| (contents == '*')){
              field.push_back(data);
              data = "";
          }
          else {
              data = data + contents;
          }

      }
      return {format, field};
  }

  bool hasCorrectNumberOfFields(SentenceData sentenceFields)
  {
      // Stub definition, needs implementing
      int fieldAmount = sentenceFields.dataFields.size();

      if (sentenceFields.format == "GLL" && fieldAmount == 5){
          return true;
      }
      else if (sentenceFields.format == "GGA" && fieldAmount == 14) {
          return true;
      }
      else if (sentenceFields.format == "RMC" && fieldAmount ==11) {
          return true;
      }
      else {
          return false;
      }

  }

  Position positionFromSentenceData(SentenceData d)
  {
      //using namespace std; // Ken: Writing 'std::' everywhere is irritating.
      std::string latitude, longitude, northSouth, eastWest, elevation;
      char northSouth0, eastWest0;
      Position p = Position(0,0,0); // Dummy object becasue there's no default constructor available for Postion

      if (d.format == "GLL")
      {
          latitude = d.dataFields[0];
          longitude = d.dataFields[2];
          northSouth = d.dataFields[1];
          eastWest = d.dataFields[3];
          elevation = "0"; // no ele

          if (northSouth.size() == 1) {
              if (northSouth == "N") {
                  northSouth0 = northSouth[0];
              }
              else if (northSouth == "S") {
                  northSouth0 = northSouth[0];
              }
              else {
                  throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + northSouth + ". Bearings must be N or S.");
              }
          }

          else {
              throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + northSouth + ". Bearings must be a single character.");
          }

          if (eastWest.size() == 1) {
              if (eastWest == "E") {
                  eastWest0 = eastWest[0];
              }
              else if (eastWest == "W") {
                  eastWest0 = eastWest[0];
              }
              else {
                   throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + eastWest + ". Bearings must be E or W.");
              }
          }

          else {
              throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + eastWest + ". Bearings must be a single character.");
          }
          try {
              p = Position(latitude,northSouth0,longitude,eastWest0,elevation);
          } catch (const std::invalid_argument& e) {
              throw std::domain_error(std::string("Ill-formed GLL sentence field: ") + e.what());
          }
      }

      else if (d.format == "RMC")
      {
          latitude = d.dataFields[2];
          longitude = d.dataFields[4];
          northSouth = d.dataFields[3];
          eastWest = d.dataFields[5];
          elevation = "0"; // no ele

          if (northSouth.size() == 1) {
              if (northSouth == "N") {
                  northSouth0 = northSouth[0];
              }
              else if (northSouth == "S") {
                  northSouth0 = northSouth[0];
              }
              else {
                  throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + northSouth + ". Bearings must be N or S.");
              }
          }

          else {
              throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + northSouth + ". Bearings must be a single character.");
          }

          if (eastWest.size() == 1) {
              if (eastWest == "E") {
                  eastWest0 = eastWest[0];
              }
              else if (eastWest == "W") {
                  eastWest0 = eastWest[0];
              }
              else {
                  throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + eastWest + ". Bearings must be E or W.");
              }
          }
          else {
              throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + eastWest + ". Bearings must be a single character.");
          }
              try {
                  p = Position(latitude,northSouth0,longitude,eastWest0,elevation);
              } catch (const std::invalid_argument& e) {
                  throw std::domain_error(std::string("Ill-formed RMC sentence field: ") + e.what());
              }
      }

      else if (d.format == "GGA")
      {
          latitude = d.dataFields[1];
          longitude = d.dataFields[3];
          northSouth = d.dataFields[2];
          eastWest = d.dataFields[4];
          elevation = d.dataFields[8];
          if (northSouth.size() == 1) {
              if (northSouth == "N") {
                  northSouth = northSouth[0];
              }
              else if (northSouth == "S") {
                  northSouth = northSouth[0];
              }
              else {
                  throw std::domain_error(std::string("Ill-formed bearing in GGA sentence field: ") + northSouth + ". Bearings must be N or S.");
              }
          }

          else {
              throw std::domain_error(std::string("Ill-formed bearing in GGA sentence field: ") + northSouth + ". Bearings must be a single character.");
          }

          if (eastWest.size() == 1) {
              if (eastWest == "E") {
                  eastWest0 = eastWest[0];
              }
              else if (eastWest == "W") {
                  eastWest0 = eastWest[0];
              }
              else {
                  throw std::domain_error(std::string("Ill-formed bearing in GGA sentence field: ") + eastWest + ". Bearings must be E or W.");
              }
          }

          else {
              throw std::domain_error(std::string("Ill-formed bearing in GGA sentence field: ") + eastWest + ". Bearings must be a single character.");
          }
          eastWest0 = eastWest[0];
          try {
              p = Position(latitude,northSouth0,longitude,eastWest0,elevation);
          } catch (const std::invalid_argument& e)
          {
              throw std::domain_error(std::string("Ill-formed GGA sentence field: ") + e.what());
          }
      }
      return p;
  }

  std::vector<Position> readSentences(std::istream &)
  {
      // Stub definition, needs implementing
      return {};
  }
}
