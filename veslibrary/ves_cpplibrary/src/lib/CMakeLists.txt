add_subdirectory(encode)
add_subdirectory(transport)

file(GLOB COM_HDRS "common/*.h")

install(FILES ${COM_HDRS}
	DESTINATION "include/xvesagent" 
)

install(FILES ../cmake/xlogConfig.cmake
	DESTINATION "lib/cmake/xlog" 
)
