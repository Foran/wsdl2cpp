Q = @
OBJS=	main.o wsdl.o xsd.o wsdlmessage.o wsdlporttype.o wsdloperation.o
SOURCES=$(OBJS:.o=.cpp)
DEPENDS=$(SOURCES:.cpp=.d)
DEFINES=-DDEBUG -DVERSION=\"0.01a\"
LIBS=-lxml2
CC=g++
BIN=wsdl2cpp
CFLAGS=-Wall -pedantic -g -I/usr/include/libxml2

.PHONY: all test

all: $(BIN)

documentation:$(BIN)
	@echo "Generating documentation..."
	$(Q)doxygen

$(BIN):$(OBJS)
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(TESTBIN):$(TESTOBJS)
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(TESTOBJS) $(LIBS) -o $(TESTBIN)

%.h:
	@echo FORCING DEPENDENCY CHECK - HEADERFILE $@ MISSING
	$(Q)rm -f *.d

%.o: %.cpp %.d
	@echo "Compiling $<..."
	$(Q)$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@
	@cppcheck $<

%.d: %.cpp
	@echo "Generating $@..."
	$(Q)set -e; $(CC) -M $(CFLAGS) $< | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@
	$(Q)test -s $@ || rm -f $@

-include $(SOURCES:.cpp=.d)

clean:
	@echo "Cleaning Files..."
	$(Q)-rm -rf *~ $(OBJS) $(BIN) $(TESTOBJS) $(TESTBIN)

mrproper: clean
	@echo "Removing dependancies..."
	$(Q)-rm -rf $(DEPENDS) $(TESTDEPENDS)
	@echo "Removing documentation..."
	$(Q)-rm -rf documentation/*
