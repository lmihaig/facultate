module myxor(q, a, b);
    input a, b;
    output q;
    wire w1, w2, w3, w4;
      not(w1, a);
      not(w2, b);
      and(w4, w1, b);
      and(w3, w2, a);
      or(q, w3, w4);
endmodule // myxor


module myxor_tb;
    reg a, b;
    wire q, w1, w2;

    initial begin
      $dumpfile("xor.vcd");
      $dumpvars;
      //            A  B  Q
      a = 0; //     0  X  0
      b = 0; //     0  0  0
      #5 a = 1; //  1  0  1
      #5 b = 1; //  1  1  0
      #5 a = 0; //  0  1  1
      #20 $finish;
    end

    initial begin
      $monitor ("time=%0d, a=%b, b=%b, q=%b", $time, a, b , q);
    end

    myxor n1(q, a, b);
    
endmodule // myxor_tb
