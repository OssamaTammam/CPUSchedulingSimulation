CC = g++-11
CFLAGS = -std=c++11
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))
EXECUTABLE = $(BINDIR)/main.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean