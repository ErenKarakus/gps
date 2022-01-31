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

  bool hasValidSentenceStructure(std::string s)
  {
      char c;
      unsigned int i;
      if (s.empty()) return false; // Need this or next line could crash
      if (s[0] != '$') return false;
      if (s.size() < 3) return false; // Need this or next line could crash
      if (s[1] != 'G') return false;
      if (s[2] != 'P') return false;
      // cout << "Debug A" << endl;
      if (s.size() < 6) return false; // Need this or next line could crash
      c = s[3];
      if (c < 65 || c > 90) return false;
      c = s[4];
      if (c < 65 || c > 90) return false;
      c = s[5];
      if (c < 'A' || c > 'Z') return false; // Hey Ken: we can do it like this instead of using the ASCII codes.  Shall I change the previous two like this as well?
      // cout << "Debug B" << endl;
      if (s.size() < 7) return false; // Need this or next line could crash.
      if (s[6] != ',') return false;
      // cout << "Debug C" << endl;
      /*
      i = 7;
      while (true)
      {
          if (i == potentialSentence.size()) return false;
          if (potentialSentence[i] == '$') return false; // Not allowed here.
          if (potentialSentence[i] == '*') break;
          ++i;
      }
      */
      // Nadia: for-loop is better.
      for (i = 7; true; ++i)
      {
          if (i == s.size()) return false;
          if (s[i] == '$') return false; // Not allowed here.
          if (s[i] == '*') break;
      }
      // cout << "Debug D" << endl;
      if (s.size() < i+3) return false; // Note: i+3 NOT i+2.  This is confusing.
      c = s[i+1];
      if ((c < 48) || (c > 57 && c < 65) || (c > 70 && c < 97) || (c > 102)) return false;
      c = s[i+2];
      if ((c < 48) || (c > 57 && c < 65) || (c > 70 && c < 97) || (c > 102)) return false;
      // cout << "Debug E" << endl;
      // cout << potentialSentence.size() << endl;
      // cout << i << endl;
      if (s.size() != i+3) return false; // Note: i+3 NOT i+2.  This is confusing.
      // Alice: It's because indexing starts at 0, so the index number is one less.
      // Nadia: No, it's because we're using '<' rather than '<='.  We need a char at i+2, so we say < i+3.
      // Ken: But indexing normally starts at 0, and we normally use <. So why is this different?
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
