PROJECT(server_main,client_main)

ADD_EXECUTABLE(server_main 
	server_main.cpp server.cpp)

ADD_EXECUTABLE(client_main
	client_main.cpp client.cpp)

TARGET_LINK_LIBRARIES (server_main
	sfml-system sfml-network sfml-graphics sfml-audio)

TARGET_LINK_LIBRARIES (client_main
	sfml-system sfml-network sfml-graphics sfml-audio sfml-window)


