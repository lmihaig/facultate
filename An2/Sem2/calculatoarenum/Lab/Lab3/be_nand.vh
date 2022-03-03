module mynand(q, a, b);
    input a, b;
    output q;

    assign q = ~(a&b);
endmodule // nand

module nand_tb();
    reg a, b;
    wire q, w1, w2;

    initial begin
      $dumpfile("be_nand.vcd");
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
      $monitor ("time=%0d, a=%b, b=%b, q=%b", $time, a, b , q);
    end

    mynand n1(q, a, b);
    
endmodule // nand_tb