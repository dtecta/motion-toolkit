set(LIB_PUBLIC_HEADERS
  consolid.h
)

if(WIN32)
  set(CONSOLID_SOURCE consolidWin32.c snprintf.c)
else(WIN32)
  set(CONSOLID_SOURCE consolidPosix.c)
endif(WIN32)	


add_library(consolid
  ${LIB_PUBLIC_HEADERS}
  ${CONSOLID_SOURCE}
)
