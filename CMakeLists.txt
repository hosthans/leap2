cmake_minimum_required(VERSION 3.16.3)

project(leap_c VERSION "1.0.0" LANGUAGES C)

if (WIN32)
   set(ULTRALEAP_PATH_ROOT "$ENV{ProgramFiles}/Ultraleap")
elseif (APPLE)
   set(ULTRALEAP_PATH_ROOT "/Applications/Ultraleap\ Hand\ Tracking\ Service.app/Contents/LeapSDK/lib/cmake/LeapSDK")
else()
   # Linux and other OSs
   set(ULTRALEAP_PATH_ROOT "")
endif()

find_package(LeapSDK
     5
     REQUIRED
     PATHS
	 	"${ULTRALEAP_PATH_ROOT}")

if (UNIX)    
    find_package(Threads REQUIRED)    
endif (UNIX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/headers")

add_executable(
	leap_c
	"main.c" src/connection.c src/fileOperations.c src/timeStamping.c)

target_link_libraries(
	leap_c
	PRIVATE
		LeapSDK::LeapC)

get_target_property(
	LEAPC_IMPORTED_CONFIG
	LeapSDK::LeapC
	IMPORTED_CONFIGURATIONS
)

get_target_property(
	LEAPC_SHARED_LIB_PATH
	LeapSDK::LeapC
	IMPORTED_LOCATION_${LEAPC_IMPORTED_CONFIG}
)

add_custom_command(
	TARGET
		leap_c
	POST_BUILD
	COMMAND
		${CMAKE_COMMAND} -E copy
		${LEAPC_SHARED_LIB_PATH}
		$<TARGET_FILE_DIR:leap_c>)



# Add targets for each sample file.
function(add_sample sample_name sample_source_file)

  add_executable(${sample_name} ${sample_source_file})
  set_property(TARGET ${sample_name} PROPERTY FOLDER "Samples")
  target_link_libraries(${sample_name} PUBLIC libExampleConnection)

endfunction()

