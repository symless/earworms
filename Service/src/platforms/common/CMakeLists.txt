
set(headers
	${CMAKE_CURRENT_SOURCE_DIR}/pinger/pinger.h
	${CMAKE_CURRENT_SOURCE_DIR}/pinger/icmp_header.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/pinger/ipv4_header.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/server/apiServer.h
	${CMAKE_CURRENT_SOURCE_DIR}/networking.hpp
	PARENT_SCOPE
)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/pinger/pinger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server/apiServer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networking.cpp
	PARENT_SCOPE
)




