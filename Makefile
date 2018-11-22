# Compiler
CC=g++

# Objects directory
ODIR=bin
# Inludes directory
IDIR=include
# Source directory
SDIR=source
# Dependecies directory
DDIR=.depends
# Tests directory
TDIR=tests
# target
TARGET=puzzle_solver

# library name
LIBNAME=example

# Compilation flags
CFLAGS=-g -std=c++11 -I$(IDIR)/ 

# Create dependencies directory
$(shell mkdir -p $(DDIR) > /dev/null)
# Dependencies generation flags
DFLAGS=-MT $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $<) -MMD -MP -MF $(DDIR)/$*.d

# Object list (derived from source directory)
_OBJS=$(patsubst $(SDIR)/%.cpp, %.o, $(shell shopt -s nullglob && echo $(SDIR)/*.cpp))
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))

main: $(OBJS)
	mkdir -p $(ODIR)
	$(CC) $< -o $(ODIR)/$(TARGET) 

# build objects
$(ODIR)/%.o: $(SDIR)/%.cpp $(DDIR)/%.d
	mkdir -p $(ODIR)
	$(CC) -c $(DFLAGS) $(CFLAGS) -o $@ $<


# empty rule, so make do not fail if dependency file do not exist (e.g firt make after make clean)
$(DDIR)/%.d: ;
.PRECIOUS: $(DDIR)/%.d

# include dependencies
-include $(DDIR)/*.d

# clean directory
clean:
	rm -f $(ODIR)/* ${DDIR}/* ./**/{*~,.*~,.*.sw?} ./{*~,.*~,.*.sw?} $(LDIR)/lib$(LIBNAME).a

.PHONY: clean make-lib all lib
