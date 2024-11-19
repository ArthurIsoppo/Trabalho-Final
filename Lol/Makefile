# Nome do compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++11 -Wall

# Nome do executável
TARGET = champions

# Arquivos de origem
SRCS = Main.cpp Champion.cpp

# Arquivos de objeto
OBJS = $(SRCS:.cpp=.o)

# Regra padrão para compilar todos os arquivos
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS)	-o	$@	$^

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS)	-c	$<

# Regra para limpar arquivos compilados
clean:
	rm	-f	$(TARGET) $(OBJS)

# Regra para limpar todos os arquivos gerados
.PHONY: all clean
