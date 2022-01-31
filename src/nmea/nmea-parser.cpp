// #include <iostream> // For debugging
#include <stdexcept>

#include "nmea-parser.h"

namespace GPS::NMEA
{
  bool isSupportedFormat(std::string)
  {
      // Stub definition, needs implementing
      return false;
  }

  bool hasValidSentenceStructure(std::string)
  {
      // Stub definition, needs implementing
      return true;
  }

  bool checksumMatches(std::string)
  {
      // Stub definition, needs implementing
      return false;
  }

  SentenceData parseSentence(std::string)
  {
      // Stub definition, needs implementing
      return {"",{}};
  }

  bool hasCorrectNumberOfFields(SentenceData)
  {
      // Stub definition, needs implementing
      return true;
  }

  Position positionFromSentenceData(SentenceData)
  {
      // Stub definition, needs implementing
      return Position(0,0,0);
  }

  std::vector<Position> readSentences(std::istream &)
  {
      // Stub definition, needs implementing
      return {};
  }
}
