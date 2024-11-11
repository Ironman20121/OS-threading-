# Teaching Assistant Student Doubt Clarification Simulation

This repository contains a C++ simulation for a Teaching Assistant (TA) system that clarifies student doubts.

- repo link 

 ```bash
 git clone https://github.com/Ironman20121/OS-threading-.git 
 cd OS-threading-.git
 ```


**Project Structure**

* **src folder:** Contains the C++ code for the simulation, including the main program (`main.cxx`).
* **CMakeLists.txt:** Configuration file for CMake, a build system.
* **Docker_tar_folder:** Stores a Docker image archive (`programming_assignment.tar`) that allows you to run the simulation without manual setupit is big file so gzip file using gunzip or use 7zip in windows.
* **Dockerfile:** Defines the instructions for building the Docker image

it contains in part files as I need split even after compressing 

```bash
cat part_aa part_ab part_ac part_ad part_ae part_af part_ag part_ah part_ai part_aj part_ak > programming_assignment.tar.gz
```
* **log folder:** (Optional) May contain output information and debugging logs , to see output using info log .

**Running the Simulation**

Here are several methods to run the TA simulation:

**Method 1: Using Docker (Recommended)**

* **Installation:**
    * **Windows:** Install Docker Desktop from the official website (https://www.docker.com/products/docker-desktop).
    * **Linux/macOS:** Follow the installation instructions on the Docker documentation (https://docs.docker.com/engine/install/).
* **Instructions:**
    1. **Download the repository.**
    2. **Navigate to the `Docker_tar_folder` directory:**
        ```bash
        cd Docker_tar_folder/
        ```
    3. **Load the Docker image:**
        ```bash
        docker load -i programming_assignment.tar
        ```
    4. **Verify the loaded image:**
        ```bash
        docker images
        ```
    5. **Run the simulation (interactive mode):**
        ```bash
        docker run -it programming_assignment
        ```
    * **Benefits of Docker:**
        * No need to set up the build environment manually.
        * Simplifies execution across different operating systems.

**Method 2: Running the C++ File Directly**

* **Requirements:**
    * A C++ compiler, such as Visual Studio (Windows) or g++ (Linux/macOS).
* **Instructions:**
    1. **Open the `main.cxx` file in your preferred code editor.**
    2. **Compile and run the code using your compiler:**
        * **Windows:** Use Visual Studio or a command-line compiler.
        * **Linux/macOS:**
            ```bash
            g++ -pthread -o pro main.cxx
            ./pro
            ```
            (Optional) Provide an argument to specify the number of students:
            ```bash
            ./pro argument={Number of Students}
            ```

**Method 3: Building with CMake**

* **Requirements:**
    * CMake installed on your system.
* **Instructions:**
    1. **Create a build directory:**
        ```bash
        mkdir build && cd build
        ```
    2. **Configure the build with CMake:**
        ```bash
        cmake ..
        ```
    3. **Build the project:**
        ```bash
        make
        ```
    4. **Run the simulation:**
        ```bash
        ./pro
        ```
        (Optional) Provide an argument to specify the number of students:
        ```bash
        ./pro argument={Number of Students}
        ```

**Method 4: Building a Docker Image from Scratch**

* **Instructions:**
    1. **Navigate to the directory containing the `Dockerfile`:**
        ```bash
        cd <path/to/repository>
        ```
    2. **Build the Docker image:**
        ```bash
        docker build -t programming_assignment .
        ```
    3. **Run the simulation (interactive mode):**
        ```bash
        docker run -it programming_assignment
        ```
