#
# Interview exercise code to calculate the angle between the hands of a clock
# Two calculation methods are compared, using cos of angle from dot product
# and direct difference from angles.
# First method uses more compute (trig functions) but gives answer without need
# to differentiate negative and reentrant angles
#

import math

twopi = 3.141592653589793238463*2.0 #math.pi*2
# explicit literal and pi from math give same answers, just below exact values (differs from C++)

#
# Represents 2D vector (x,y)
# Defines dot product to get cos of angle between 2 vectors
#
class Vec2d:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    def dot(self,v):
        return self.x*v.x + self.y*v.y

#
# Base class for clock hand, subclasses HourHand, MinuteHand
#
class Hand:
    # class constants to define minutes in an hour and hours on a clockface
    # may be overwritten by the using code via the set_params() method
    MINSPERHR = 60.0
    HRSPERCLOCK = 12.0

    # sets the hour/minute parameters
    @classmethod
    def set_params(cls,mph,hpc):
        cls.MINSPERHR = mph
        cls.HRSPERCLOCK = hpc

    # constructor setting time (hour or minute determined by subclass)
    def __init__(self,time):
        self.time = time

    # sets an angle with respect to the vertical
    # sets a unit vector for that angle
    def set_vector(self,angle):
        self.angle = angle
        self.vector = Vec2d( math.cos(angle), math.sin(angle))

    # calculates the difference in the angle between two hands
    # allowing/correcting for reentrant and negative angles
    def diff_angle(self, hand):
        diff = math.fabs( self.angle - hand.angle )
        if diff > twopi/2.0: diff = twopi - diff
        return diff

# Hand subclass for hour hand
class HourHand(Hand):
    # constructor setting time/hour in continuous increment by minutes
    # sets the vertical angle and its vector
    def __init__(self,hour,min):
        super().__init__(hour+min/Hand.MINSPERHR)
        super().set_vector( twopi*self.time/Hand.HRSPERCLOCK )

# Hand subclass for minute hand
class MinuteHand(Hand):
    # constructor setting time from minutes
    # and corresponding angle and vector
    def __init__(self,min):
        super().__init__(min)
        super().set_vector( twopi*self.time/Hand.MINSPERHR )

# main program asking for hour/minute input
# and printing the angle based on dot product between vectors
# and also angle based on difference between angle of handss
def main():
    # set parameters for clock
    Hand.set_params(60.0, 12.0)
    while True:
        hour = float( input("Enter hour value (<0 quits): ") )
        if hour<0: break
        min  = float( input("Enter minute value: ") )
        hhand = HourHand(hour,min)
        mhand = MinuteHand(min)
        cosangle = hhand.vector.dot( mhand.vector)
        angle = (360.0/twopi)*math.acos(cosangle)
        print(F"(dotproduct method) angle is {angle}")
        angle = (360.0/twopi)*hhand.diff_angle(mhand)
        print(F"(angledifference method) angle is {angle}")

if __name__ == '__main__':
    main()