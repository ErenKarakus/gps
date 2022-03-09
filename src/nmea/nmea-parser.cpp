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
      return false;
  }

  bool hasValidSentenceStructure(std::string s)
  {
      std::regex expression("(\\$GP)([A-Z]){3},(\\w|[.]|[,]){0,}\\*[[:xdigit:]]{2}");
      return std::regex_match(s, expression);
  }

  bool checksumMatches(std::string s)
  {
      // Stub definition, needs implementing
      std::regex expression("(?!\\$)(\\w|,|.)+\\*");
      std::smatch matches;
      std::string match;

      std::regex_search(s, matches, expression);
      match = matches[0];
      return false;
  }

  SentenceData parseSentence(std::string)
  {
      // Stub definition, needs implementing
      return {"",{}};
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
              northSouth0 = northSouth[0];
          } else {
              throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + northSouth + ". Bearings must be a single character.");
          }
          if (eastWest.size() == 1) {
              eastWest0 = eastWest[0];
          } else {
              throw std::domain_error(std::string("Ill-formed bearing in GLL sentence field: ") + eastWest + ". Bearings must be a single character.");
          }
          try
          {
                p = Position(latitude,northSouth0,longitude,eastWest0,elevation);
          }
          catch (const std::invalid_argument& e)
          {
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
          if (northSouth.size() != 1) {
              throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + northSouth + ". Bearings must be a single character.");
          } else {
              northSouth0 = northSouth[0];
          }
          if (eastWest.size() != 1) {
              throw std::domain_error(std::string("Ill-formed bearing in RMC sentence field: ") + eastWest + ". Bearings must be a single character.");
          } else {
              eastWest0 = eastWest[0];
          }
          try {
            p = Position(latitude,northSouth0,longitude,eastWest0,elevation);
          }
          catch (const std::invalid_argument& e) {
            throw std::domain_error(std::string("Ill-formed RMC sentence field: ") + e.what());
          }
      } else if (d.format == "GGA")
      {
          latitude = d.dataFields[1];
          longitude = d.dataFields[3];
          northSouth = d.dataFields[2];
          eastWest = d.dataFields[4];
          elevation = d.dataFields[8];
          if (northSouth.size() != 1) {
              throw std::domain_error(std::string("Ill-formed bearing in GGA sentence field: ") + northSouth + ". Bearings must be a single character.");
          }
          northSouth0 = northSouth[0];
          if (eastWest.size() != 1) {
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
