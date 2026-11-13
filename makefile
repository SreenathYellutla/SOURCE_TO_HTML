CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o evaluation.o s_html.o parcer.o html.o keyword.o
HDRS = header.h html.h keyword.h s_html.h

source2html.out: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o source2html.out