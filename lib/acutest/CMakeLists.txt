add_library(acutest INTERFACE)
target_include_directories(acutest INTERFACE include)
target_link_options(acutest INTERFACE
  --redirect=_Printf=_PrintfFullNoMb
  --semihosting)
