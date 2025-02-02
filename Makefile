
STOQ	= stoq
QTOS	= qtos
STOQ_SRCS	= stoq.cpp
QTOS_SRCS	= qtos.cpp
CC	= g++

all: $(STOQ) $(QTOS)

$(STOQ):
	$(CC) $(STOQ_SRCS) -o $(STOQ)

$(QTOS):
	$(CC) $(QTOS_SRCS) -o $(QTOS)

clean:
	rm $(STOQ) $(QTOS)

fclean: clean

re: fclean all

