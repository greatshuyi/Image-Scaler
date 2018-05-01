# Image-Scaler
An experimental synthesizable image scaler using HLS.

## Backgroud
HLS tend to be an promising method to design digital circuits, especially for signal processing units.


## HLS coding guide line

**First of all, HLS code usually will not have the same structure as C program code. The first thing before one start to code is structural design, which target two major aspects: communication and computation**

### Common coding guide lines

+ For a single-bit variable, use the native C++ type bool or the SystemC type sc_bit.
For variables less than 64 bits wide, use sc_int or sc_uint data types.
Use sc_uint for all logic and unsigned arithmetic operations. Use
sc_int for signed arithmetic operations as well as for logic operations.
For variables larger than 64 bits, use sc_bigint or sc_biguint if you
want to do arithmetic operations with these variables. If you want to
do logic operations, use sc_bv instead.

Use native C++ integer types for loop counters or when you need a
variable of the size defined by the native C++ type. 


Use the C++ enum for all enumerated types – for example, state
variables. Use the C++ struct for all aggregate types.

It is strongly recommended that you do not use data members for
storage. Use variables local to the process for all storage
requirements in a process

Using Clocked Thread Processes
A clocked thread process, SC_CTHREAD, is the basic unit for
behavioral synthesis with SystemC Compiler

An SC_CTHREAD process uses wait statements in the SystemC
code to synchronize reading from and writing to signals and ports in
the process. 

Each SC_CTHREAD process must have at least one wait statement.
The wait(n) statement suspends process execution for n active edges
of the clock. The default value of n is 1.

The outputs of an SC_CTHREAD process are modeled as being
registered. When an SC_CTHREAD process writes to an output
signal, the value appears after the next active edge of the clock.

When the SC_CTHREAD process is invoked, it executes statements
in the process until either a wait(n) or a wait_until(cond) statement is
encountered. The process is then suspended until the next active
edge, or it is suspended until the next active edge where the condition
of wait_until is satisfied. All variables that are local to the process are
saved when the process is suspended, which means that the process
state is implicitly saved. When the process restarts, execution
continues at the statement that follows the wait or wait_until
statement.






