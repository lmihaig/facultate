module stHA(s, co, a, b);
    input a, b;
    output reg s, co;
    always @(a or b) begin
      s = a ^ b;
      co = a & b;
    end
endmodule // stHA

module stHA_tb;
    reg a, b;
    wire s, co;

    initial begin
      $dumpfile("st_halfadder.vcd");
      $dumpvars;
      //            
      a = 0; //     
      b = 0; //     
      #5 a = 1; //  
      #5 b = 1; //  
      #5 a = 0; //  
      #20 $finish;
    end

    initial begin
      $monitor ("time=%0d, a=%b, b=%b, s=%b, co=%b ", $time, a, b , s, co );
    end

    stHA n1(s, co, a, b);
endmodule // stHA