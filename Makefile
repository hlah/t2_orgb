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
# target
TARGET_NAME=puzzle_solver

# Compilation flags
CFLAGS=-std=c++11 -I$(IDIR)/ 
DEBUGFLAGS=-g
RELEASEFLAGS=-static

# Create dependencies directory
$(shell mkdir -p $(DDIR) > /dev/null)
# Dependencies generation flags
DFLAGS=-MT $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $<) -MMD -MP -MF $(DDIR)/$*.d

# Object list (derived from source directory)
OBJS=$(patsubst $(SDIR)/%.cpp, %.o, $(shell shopt -s nullglob && echo $(SDIR)/*.cpp))

debug: $(patsubst %,$(ODIR)/debug/%,$(OBJS))
	mkdir -p $(ODIR)/debug/
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(DFLAGS) $^ -o $(ODIR)/debug/$(TARGET_NAME) 

release: $(patsubst %,$(ODIR)/release/%,$(OBJS))
	mkdir -p $(ODIR)/release/
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $(DFLAGS) $^ -o $(ODIR)/release/$(TARGET_NAME) 


# build objects
$(ODIR)/debug/%.o: $(SDIR)/%.cpp $(DDIR)/%.d
	mkdir -p $(ODIR)/debug/
	$(CC) -c $(DFLAGS) $(DEBUGFLAGS) $(CFLAGS) -o $@ $<

$(ODIR)/release/%.o: $(SDIR)/%.cpp $(DDIR)/%.d
	mkdir -p $(ODIR)/release/
	$(CC) -c $(DFLAGS) $(RELEASEFLAGS) $(CFLAGS) -o $@ $<


# empty rule, so make do not fail if dependency file do not exist (e.g firt make after make clean)
$(DDIR)/%.d: ;
.PRECIOUS: $(DDIR)/%.d

# include dependencies
-include $(DDIR)/*.d

# clean directory
clean:
	rm -rf $(ODIR)/* ${DDIR}/* ./**/{*~,.*~,.*.sw?} ./{*~,.*~,.*.sw?} $(LDIR)/lib$(LIBNAME).a

.PHONY: clean make-lib all lib
