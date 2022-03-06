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
      std::regex expression("(\\$GP)([A-Z]){3},(\\w|\\.|\\,){0,}\\*([A-F]|[a-f]|[0-9]){2}");
      return std::regex_match(s, expression);
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
      using namespace std; // Ken: Writing 'std::' everywhere is irritating.
      string la, lo, ns, ew, e;
      char ns0, ew0;
      Position p = Position(0,0,0); // Dummy object becasue there's no default constructor available for Postion
      if (d.format == "GLL")
      {
          la = d.dataFields[0];
          lo = d.dataFields[2];
          ns = d.dataFields[1];
          ew = d.dataFields[3];
          e = "0"; // no ele
          if (ns.size() == 1) {
              ns0 = ns[0];
          } else {
              throw domain_error(string("Ill-formed bearing in GLL sentence field: ") + ns + ". Bearings must be a single character.");
          }
          if (ew.size() == 1) {
              ew0 = ew[0];
          } else {
              throw domain_error(string("Ill-formed bearing in GLL sentence field: ") + ew + ". Bearings must be a single character.");
          }
          try
          {
                p = Position(la,ns0,lo,ew0,e);
          }
          catch (const invalid_argument& e)
          {
                throw domain_error(string("Ill-formed GLL sentence field: ") + e.what());
          }
      }
      else if (d.format == "RMC")
      {
          la = d.dataFields[2];
          lo = d.dataFields[4];
          ns = d.dataFields[3];
          ew = d.dataFields[5];
          e = "0"; // no ele
          if (ns.size() != 1) {
              throw domain_error(string("Ill-formed bearing in RMC sentence field: ") + ns + ". Bearings must be a single character.");
          } else {
              ns0 = ns[0];
          }
          if (ew.size() != 1) {
              throw domain_error(string("Ill-formed bearing in RMC sentence field: ") + ew + ". Bearings must be a single character.");
          } else {
              ew0 = ew[0];
          }
          try {
            p = Position(la,ns0,lo,ew0,e);
          }
          catch (const invalid_argument& e) {
            throw domain_error(string("Ill-formed RMC sentence field: ") + e.what());
          }
      } else if (d.format == "GGA")
      {
          la = d.dataFields[1];
          lo = d.dataFields[3];
          ns = d.dataFields[2];
          ew = d.dataFields[4];
          e = d.dataFields[8];
          if (ns.size() != 1) {
              throw domain_error(string("Ill-formed bearing in GGA sentence field: ") + ns + ". Bearings must be a single character.");
          }
          ns0 = ns[0];
          if (ew.size() != 1) {
              throw domain_error(string("Ill-formed bearing in GGA sentence field: ") + ew + ". Bearings must be a single character.");
          }
          ew0 = ew[0];
          try {
            p = Position(la,ns0,lo,ew0,e);
          } catch (const invalid_argument& e)
          {
              throw domain_error(string("Ill-formed GGA sentence field: ") + e.what());
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
