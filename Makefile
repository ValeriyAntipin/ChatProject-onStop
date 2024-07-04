# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++11

# Исходные файлы
SRCS = User.cpp Message.cpp Chat.cpp TCPclient.cpp TCPserver.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемые файлы
TARGETS = TCPclient TCPserver

# Правило по умолчанию
all: $(TARGETS)

# Создание исполняемого файла TCPclient
TCPclient: User.o Message.o Chat.o TCPclient.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Создание исполняемого файла TCPserver
TCPserver: User.o Message.o Chat.o TCPserver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции исходных файлов
%.o: %.
