/*
    In 4_sensor_2.cpp we saw how to register observers for specific kind of notificaitons.

    Now, assume there are multiple subjects (sensors). The objects want to depend on readings from different
    kinds of sensors, e.g. temperature, wind-speed, rainfall

    If  the observers depend on multiple subject then there will be lot of dependencies between the classes.
    All the objects will have to keep track of their subjets.

    One way of reducing the dependecy between the subjects and the observers is to indroduce
    another component and that component will take care of the interaction between the subject
    and the observers. It is called the "Change-Manager"

    When the subjects observe a change they will send a notificaiton to the change manager and the change manager
    notifies the observers.
    The change manager is an example of the mediator design pattern.
*/