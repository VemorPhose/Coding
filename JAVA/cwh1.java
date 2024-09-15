public class cwh1 {
    public void localVar(){
        String name2 = "Ben"; // note: DOUBLE QUOTES WITH STRINGS.
        int marks2 = 90;
        System.out.println(marks2 + ' ' + name2);
    }

    public void notlocalVar(){
        // System.out.println(name2 + " scored " + marks + "%."); // ---> gives error - var_name cannot be resolved to a variable.
    }

    // instance variable
    public int glob = 5; // basically a global variable, defined within class but outside all methods. similar to static variables.
    public static int marks3 = 80; // static variables defined in class. can be accessed by all methods and constructors.
    public static void main(String[] args) {
        System.out.println("Hello World");
        // single line comment
        /* multi 
         * line
         * comment
         */
        // https://pastebin.com/ZxnV2Xvq

        // variable declaration
        int marks = 50;
        String name = "ram"; 

        // compound printing
        System.out.println(name + " scored " + marks + "%."); 
        // note: 'println' prints line and moves pointer to next line,
        // 'print' prints a statement and keeps pointer at end of current line.

        // note: objects or methods within a class have their own local variable scopes and they do not share them.
        cwh1 vt = new cwh1();
        vt.notlocalVar(); // would give error as stated above beside method.

        
    }
}
