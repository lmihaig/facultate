module stFS(d, bo, a, b, bi);
    output reg d, bo;
    input a, b, bi;
    always @(a or b or bi) begin
        d = a ^ b ^ bi;
        bo = ~a&b | bi & (~a|b);
    end
endmodule // stFS

module arith_tb;
    reg a, b, bi;
    wire s, bo;

    initial begin
      $dumpfile("st_fullsubstractor.vcd");
      $dumpvars;
      //            
      a = 0; //     
      b = 0; //     
      bi = 0;
      #5 bi = 1;
      #5 b = 1; //  
      #5 bi = 0;
      #5 a = 1; //  
      #5 bi = 1;
      #5 b = 0;
      #20 $finish;
    end

    initial begin
      $monitor ("time=%0d, a=%b, b=%b, bi=%b, d=%b, bo=%b ", $time, a, b,bi, d, bo );
    end

    stFS n1(d, bo, a, b, bi);
endmodule // arith_tb