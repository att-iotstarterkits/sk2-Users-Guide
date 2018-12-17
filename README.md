# sk2-Users-Guide
Users guide for AT&T IoT Starter kit (2nd generation) - also known as SK2 - with associated code examples

The User's Guide is broken into a series of chapters:

1. Getting Started

    The first chapter is all about getting started with the SK2. After a brief introduction to the kit itself, you’ll begin by registering your kit’s SIM card and then working through the QuickStart application that comes programmed into the SK2.
    
    The second part of the QuickStart lets you view the sensor data sent by your SK2 on a pre-built Asset Tracking dashboard that located in the AT&T IoT Marketplace.

2. Using Embedded Linux

    The SK2 runs a tiny distribution of Linux. If you’ve used Linux before then you already know most of what’s in this chapter. Along with showing you how to connect your personal computer to the kit, this chapter provide a quick primer for running Linux on the SK2.

3. Programming with C

    The SK2 can be programmed using the C programming language. In essence, you can write C Linux application to control the SK2 module. The SK2 is supported by two C callable libraries which let you access the on-board peripherals as well as the LTE communications.
    
    This chapter takes you through installing the C programming environment and writing your first C program. Once complete, you should be able to control the on-board LED and read the User Switch by programming the pins attached to those controls via the GPIO (general purpose bit I/O) API (applications programming interface).

4. Programming with Python

   The fourth chapter accomplishes the same goals as Chapter 3, but using Python. Therefore, in this chapter we will learn how to install a new Python-based image to the SK2 as well as use it to read the User Switch and toggle the LED.

5. Connecting to the Cloud with LTE

    One of the unique capabilities of the SK2 is its ability to communicate over the AT&T LTE wireless connection. This allows untethered, mobile access to the Internet. In this chapter you will learn how to connect to the Cloud to send and receive data. This chapter leverages the connectivity libraries to support both programming languages (Python and C).

6. Using I2C with the Accelerometer

    I²C (pronounced I-squared-C) is a common serial communications port widely used on microcontrollers and processors. Alternatively, it’s also called an I2C port, as this is easier to write in simple text files.
    
    This serial port is widely used for communicating with lower-speed peripherals across short-distances within a board. One of the main differences between other types of serial ports (SPI or UART) is that I2C ports support a simple addressing mechanism which allows them to connect multiple devices together across a single port.
    
    Conveniently, the SK2 contains an on-board sensor (the accelerometer) which is connected to our Linux processor by way of the I2C port. This makes it makes it easy to experiment with the I2C port as we learn about how it works.

7. Using the ADC with the Light Sensor

    The ADC (analogue to digital converter) is another useful peripheral interface found on the SK2’s Linux processor. This port converts real-world analogue signals (i.e. voltages) into digital values (i.e. numbers) that we can use to observe our environment. In this case, the on-board light sensor is connected to our Linux processor through the ADC peripheral interface. 
    
    As the light landing on the sensor gets brighter or dimmer, the light sensor outputs a greater or lesser voltage. Our Linux programs (either using C or Python) can read a numerical representation of the voltage via the ADC port.

8. Getting the Location Using GPS

    GPS (global positioning system) is another popular sensor built into the SK2. In fact, this one is notable in that the GPS antenna is one of the three wires that need to be connected when first assembling the kit. 
    
    If you have a phone, or a GPS unit in your car, then you already know that GPS systems provide location data by reading signals sent by orbiting satellites. We won’t get too deep into how GPS works but we’ll examine how your programs can retrieve location data from the GPS sensor to use locally or pass along to the Cloud for further processing or tracking.

This github repository contains the code examples that have been developed along with the SK2 Users Guide.
