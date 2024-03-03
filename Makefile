TARGET = webserver
INCLUDE =  ./include
VPATH = ./src/
SRC = main.c
BUILDDIR = ./objs/
OBJS = $(addprefix $(BUILDDIR), $(SRC:.c=.o))


all: $(TARGET)

$(TARGET): $(OBJS)
	cc $(OBJS) -I$(INCLUDE) -o $(TARGET)

$(BUILDDIR)%.o: %.c $(BUILDDIR)
	cc $< -I $(INCLUDE) -c -o $@

$(BUILDDIR):
	test -d $(BUILDDIR) || mkdir $(BUILDDIR)
