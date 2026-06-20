# syntax=docker/dockerfile:1
#
# Multi-stage build. Two named targets give you a choice of image:
#
#   Slim, run-only image (default):
#     docker build --target runtime -t dsa:slim .
#     docker run -it dsa:slim
#
#   Full development image (compiler + valgrind + gdb inside):
#     docker build --target dev -t dsa:dev .
#     docker run -it dsa:dev
#
# Note: dsa is an interactive ncurses menu, so it needs `docker run -it`.

# ---------- Stage 1: dev — full toolchain, debug-ready (heavyweight) ----------
FROM ubuntu:24.04 AS dev

# Prevent interactive timezone/keyboard prompts from freezing the build
ENV DEBIAN_FRONTEND=noninteractive

# Full build + debug toolchain: compiler, make, valgrind, gdb, ncurses headers
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    valgrind \
    gdb \
    libncurses-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the whole repo so you can also rebuild/debug from inside this image
COPY . .

# Compile fresh inside the container
RUN make clean && make

CMD ["./dsa"]

# ---------- Stage 2: runtime — binary + ncurses runtime only (slim) ----------
FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

# Only the ncurses RUNTIME library the binary links against (-lncurses).
# No compiler, no headers, no valgrind/gdb, no source.
RUN apt-get update && apt-get install -y \
    libncurses6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Pull only the compiled binary out of the dev stage
COPY --from=dev /app/dsa .

CMD ["./dsa"]
