set(LIB_PUBLIC_HEADERS
  rand32.h 
  consolid.h
)
	
add_library(consolid
  ${LIB_PUBLIC_HEADERS}
  rand32.c
  snprintf.c
)
