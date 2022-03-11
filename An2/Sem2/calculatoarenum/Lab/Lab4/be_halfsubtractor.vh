module beHS(d, bo, a, b);
    input a, b;
    output wire d, bo;
    
    assign {bo, d} = a&-b;
endmodule // beHS

module beHS_tb;
    reg a, b;
    wire d, bo;

    initial begin
      $dumpfile("be_halfsubtractor.vcd");
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
      $monitor ("time=%0d, a=%b, b=%b, d=%b, bo=%b ", $time, a, b, d, bo);
    end

    beHS n1(d, bo, a, b);
endmodule // beHS