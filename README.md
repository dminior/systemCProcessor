# SystemC Processor Design
## Overview
Welcome to the SystemC Processor Design project! This project focuses on implementing a processor using the `SystemC` language. SystemC is a powerful `C++` library that allows designers to model hardware at different levels of abstraction, making it an ideal choice for processor design.

## Project Structure
The project consists of several modules corresponding to individual elements of the actual structure of the processor:

* `aluModule`: Performing arithmetic and logical operations. It takes input from the register file or memory and produces output based on the control signals received.
  
* `controlModule`: Manages the control signals for the processor. It interprets instruction opcodes and generates the necessary control signals to coordinate the execution of instructions.
  
* `registerModule`: Managing the processor's registers. It stores and retrieves data, facilitating the movement of information between different stages of the pipeline.
  
* `memorySystemModule`: Manages the interaction between the processor and external memory. It handles read and write operations to and from memory.
  
* `main`: Serves as the entry point for the SystemC simulation. It orchestrate the initialization of other modules, set up simulation parameters, and run the simulation loop.

> [!IMPORTANT]
>Before starting, ensure you have the SystemC library installed. Download and install the SystemC library from www.accellera.org.
