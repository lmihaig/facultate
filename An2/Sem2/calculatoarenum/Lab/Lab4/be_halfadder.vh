module beHA(s, co, a, b);
    input a, b;
    output wire s, co;
    
    assign{co, s} = a+b;
endmodule // beHA

module beHA_tb;
    reg a, b;
    wire s, co;

    initial begin
      $dumpfile("be_halfadder.vcd");
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
      $monitor ("time=%0d, a=%b, b=%b, s=%b, co=%b ", $time, a, b, s, co);
    end

    beHA n1(s, co, a, b);
endmodule // beHA