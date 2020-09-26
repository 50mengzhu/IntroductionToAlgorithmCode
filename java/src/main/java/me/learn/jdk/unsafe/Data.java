package me.learn.jdk.unsafe;

public class Data {

    private int id;

    private String name;

    public Data() {
        System.out.println("hello");
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return id + " :" + name;
    }
}
