##
## EPITECH PROJECT, 2022
## generic makefile
## File description:
## Makefile
##

TARGET			=		nanotekspice


SRCDIR			=		./src
SRC_EXTENSION	=		cpp
ENTRYPOINT		=		$(SRCDIR)/main.$(SRC_EXTENSION)
SRC				=		$(shell find $(SRCDIR)/**/*.$(SRC_EXTENSION)) $(shell find $(SRCDIR)/**/**/*.$(SRC_EXTENSION))
ALLSRC			=		$(SRC) $(ENTRYPOINT)


OBJDIR			=		obj
OBJ				=		$(patsubst %.$(SRC_EXTENSION), %.o, $(ALLSRC))
CC				=		g++
ifneq ("$(wildcard /bin/ccache)","")
  CC := ccache g++
endif
HEADERS			=		include
LDFLAGS			=		-I $(HEADERS)
CFLAGS			=		-Wall -Wextra -g -Werror

UTDIR			=		tests/unit_tests
UTSRC			=		$(shell find $(UTDIR)/*.$(SRC_EXTENSION))
UTEST_FILES		=		$(SRC) $(UTSRC)
UTEST_TARGET	=		unit_tests
UTFLAGS			=		$(CFLAGS) $(LDFLAGS) --coverage -lcriterion


.RECIPEPREFIX	=	-
.PHONY: clean fclean re objfolder run_tests clean_tests



all: $(TARGET)
- @echo -e "|||||||||||||||| Build Complete |||||||||||||||||||"
- @echo -e "Binary name: $(TARGET)"

$(TARGET): $(OBJ)
- $(CC) $(LDFLAGS) -o $(TARGET) $(OBJ)

clean: clean_tests
-rm -f *.o
-rm -rf $(OBJ)

clean_tests:
-rm -f *.gc*
-rm -f $(UTEST_TARGET)


fclean: clean
-rm -f $(TARGET)
-rm -rf $(OBJDIR)
-rm -f $(UTEST_TARGET)

re: fclean all

objfolder: |	$(OBJDIR)

run_tests:	clean_tests $(UTEST_TARGET)

$(UTEST_TARGET):	$(UTEST_FILES)
- @echo "SRC: " $(SRC)
-$(CC) -o $(UTEST_TARGET) $(UTFLAGS) $(UTEST_FILES)
-./$(UTEST_TARGET)
-gcovr

$(OBJDIR):
-@ echo "recreating obj dir"
- mkdir -p $(OBJDIR)

%.o: %.cpp
-$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

