package me.learn.jdk;

class Guard {

    private double string = 32.0;

    private double aDouble = 33.0;

    private double bDouble = 34.0;

//    private int ACCESS_ALLOWED = 1;
//
//    private int ACCESS_ALLOWED_2 = 1;

//    private short hello = 34;
//    private short hello1 = 34;
    private boolean m = true;

//    private int ACCESS_ALLOWED_1 = 1;

    public boolean giveAccess() {
//        return 42 == ACCESS_ALLOWED;
        return false;
    }

    public double getString() {
        return string;
    }

    public void setString(double string) {
        this.string = string;
    }

    public double getaDouble() {
        return aDouble;
    }

    public void setaDouble(double aDouble) {
        this.aDouble = aDouble;
    }

    public double getbDouble() {
        return bDouble;
    }

    public void setbDouble(double bDouble) {
        this.bDouble = bDouble;
    }
}