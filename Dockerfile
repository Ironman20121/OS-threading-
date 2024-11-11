# Use an official C++ image with CMake
FROM gcc:latest

# Install CMake
RUN apt-get update && apt-get install -y cmake

# Set the working directory
WORKDIR /usr/src/app

# Copy the CMakeLists.txt and source code into the container
COPY . .

# Create a build directory
RUN mkdir -p build && cd build && rm -rf * && cmake .. && make

# Command to run the compiled application
CMD ["./build/pro"]

