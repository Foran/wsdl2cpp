Q = @
OBJS=	main.o wsdl.o xsd.o wsdlmessage.o wsdlporttype.o \
	wsdloperation.o wsdlmessagepart.o xsdelement.o \
	xsdsimpletype.o xsdcomplextype.o civetweb.o
SOURCES=$(OBJS:.o=.cpp)
DEPENDS=$(SOURCES:.cpp=.d)
DEFINES=-DDEBUG -DVERSION=\"0.01a\"
LIBS=-lxml2 -ldl -lpthread
INCLUDES=-I/usr/include/libxml2 -Icivetweb/include
CC=g++
BIN=wsdl2cpp
CFLAGS=-Wall -g $(INCLUDES)
CPPFLAGS=$(CFLAGS) -pedantic -std=c++0x
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

civetweb.o: civetweb/src/civetweb.c civetweb/include/civetweb.h
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -x c -c $< -o $@

%.o: %.cpp %.d
	@echo "Compiling $<..."
	$(Q)$(CC) $(CPPFLAGS) $(DEFINES) -c $< -o $@
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
	$(Q)-rm -rf documentation/
