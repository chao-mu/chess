FROM silkeh/clang

WORKDIR /app

# Requires...
#   bison, flex - main build
#   doxygen     - doc build
#   valgrind    - tests
RUN apt-get update \
    && apt-get install -y bison flex valgrind doxygen

# Copy only what is needed
COPY src .
COPY Makefile .
COPY tests .
COPY projects .
COPY assets . 
COPY Doxyfile .

# Build everything and test it.
RUN make all
RUN make doc
RUN make test
