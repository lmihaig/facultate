module stFA(s, co, a, b, ci);
    output reg s, co;
    input a, b, ci;
    always @(a or b or ci) begin
        s = a ^ b ^ ci;
        co = a&b | ci & (a|b);
    end
endmodule // stFA

module arith_tb;
    reg a, b, ci;
    wire s, co;

    initial begin
      $dumpfile("st_fulladder.vcd");
      $dumpvars;
      //            
      a = 0; //     
      b = 0; //     
      ci = 0;
      #5 ci = 1;
      #5 b = 1; //  
      #5 ci = 0;
      #5 a = 1; //  
      #5 ci = 1;
      #5 b = 0;
      #20 $finish;
    end

    initial begin
      $monitor ("time=%0d, a=%b, b=%b, ci=%b, s=%b, co=%b ", $time, a, b,ci, s, co );
    end

    stFA n1(s, co, a, b, ci);
endmodule // arith_tb