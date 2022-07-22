// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  std::string ansi_to_utf8( const char* str, uint ansi_codepage = ANSI_CODEPAGE_DEFAULT ) {
    std::string res;
    int result_u, result_c;
    result_u = MultiByteToWideChar( ansi_codepage, 0, str, -1, 0, 0 );
    if ( !result_u ) { return 0; }
    wchar_t* ures = new wchar_t[result_u];
    if ( !MultiByteToWideChar( ansi_codepage, 0, str, -1, ures, result_u ) ) {
      delete[] ures;
      return 0;
    }
    result_c = WideCharToMultiByte( 65001, 0, ures, -1, 0, 0, 0, 0 );
    if ( !result_c ) {
      delete[] ures;
      return 0;
    }
    char* cres = new char[result_c];
    if ( !WideCharToMultiByte( 65001, 0, ures, -1, cres, result_c, 0, 0 ) ) {
      delete[] cres;
      return 0;
    }
    delete[] ures;
    res.append( cres );
    delete[] cres;
    return res;
  }
}