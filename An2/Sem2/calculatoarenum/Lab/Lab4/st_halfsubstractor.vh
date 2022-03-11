module stHS(d, bo, a, b);
    input a, b;
    output reg d, bo;
    always @(a or b) begin
      d = a ^ b;
      bo = a | ~b;
    end
endmodule // stHS

module stHS_tb;
    reg a, b;
    wire d, bo;

    initial begin
      $dumpfile("st_halfsubtractor.vcd");
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
      $monitor ("time=%0d, a=%b, b=%b, d=%b, bo=%b ", $time, a, b , d, bo );
    end

    stHS n1(d, bo, a, b);
endmodule // stHS