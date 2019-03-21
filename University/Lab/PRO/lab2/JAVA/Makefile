.PHONY: clean

Lab2.class: Lab2.java Inp/Input.class Output/Output.class LastMax/LastMax.class
	javac Lab2.java
Inp/Input.class: Input.java
	javac -d . Input.java
Output/Output.class: Output.java
	javac -d . Output.java
LastMax/LastMax.class: LastMax.java
	javac -d . LastMax.java
Jar:
	jar -cfm Lab2.jar manifest.txt Lab2.class LastMax/LastMax.class Output/Output.class Inp/Input.class

clean:
	rm -rf Inp Out LastMax Lab2.jar *class
