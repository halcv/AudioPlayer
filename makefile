CC = gcc
CFLAGS = -W -Wall
OPTION = -lwiringPi -lpthread
INC = -I/usr/local/include
LIB = -L/usr/local/lib
OBJ = main.o PortManager.o MainThread.o Timer10msThread.o InputSwTimer.o InputSwProcess.o Mutex.o PlayWaitTimer.o MpcProcess.o

.SUFFICS: .c .o
AudioPlayer : $(OBJ)
	$(CC) $(OPTION) -o AudioPlayer $(OBJ)
.c.o :
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $<

main.o : MySystype.h PortManager.h MainThread.h Timer10msThread.h
PortManager.o : MySystype.h PortManager.h Board.h
MainThread.o : MySystype.h MainThread.h InputSwProcess.h MpcProcess.h
Timer10msThread.o : MySystype.h Timer10msThread.h InputSwTimer.h PlayWaitTimer.h
InputSwTimer.o : MySystype.h InputSwTimer.h Mutex.h
InputSwProcess.o : MySystype.h InputSwProcess.h InputSwTimer.h PortManager.h MpcProcess.h
Mutex.o : MySystype.h Mutex.h
PlayWaitTimer.o : MySystype.h Mutex.h PlayWaitTimer.h
MpcProcess.o : MySystype.h MpcProcess.h PlayWaitTimer.h
clean :
	rm -rf *.o
	rm -rf AudioPlayer
