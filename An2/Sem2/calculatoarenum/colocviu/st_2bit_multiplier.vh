// Licu Mihai-George CTI 262

module stMultiplier(c0,c1,c2,c3,a0,a1,b0,b1);
    // modul de implementare structural
    input a0, a1,b0,b1;
    output reg c0,c1,c2,c3;
    reg w1,w2,w3,w4;
    always @(a0 or a1 or b0 or b1) begin
        c0 = a0 & b0;
        w1 = a0&b1;
        w2 = a1&b0;
        c1 = w1^w2;
        w3 = w1&w2;
        w4 = a1&b1;
        c2 = w3^w4;
        c3 = w3&w4;
    end
    
endmodule //stMultiplier



module arith_tb;
    reg a0, a1, b0, b1;
    wire c0,c1,c2,c3;

    initial begin
        $dumpfile("st_2bit_multiplier.vcd");
        $dumpvars;
                   // 00 00
        a0 = 0;
        a1 = 0;
        b0 = 0;
        b1 = 0;

        #5
        a0 = 1; // 00 01
        #5
        a0 = 0;
        a1 = 1; // 00 10
        #5
        a0 = 1; // 00 11
        #5
        a0 = 0;
        a1 = 0;
        b0 = 1; // 01 00
        #5
        a0 = 1; // 01 01
        #5
        a0 = 0;
        a1 = 1; // 01 10
        #5
        a0 = 1; // 01 11
        #5
        a0 = 0;
        a1 = 0;
        b0 = 0;
        b1 = 1; // 10 00
        #5
        a0 = 1; // 10 01
        #5
        a0 = 0;
        a1 = 1; // 10 10
        #5
        a0 = 1; // 10 11
        #5
        a0 = 0;
        a1 = 0;
        b0 = 1; // 11 00
        #5
        a0 = 1; // 11 01
        #5
        a0 = 0;
        a1 = 1; // 11 10
        #5
        a0 = 1; // 11 11


        #20 $finish;  
    end

    initial begin
      $monitor ("time=%0d, a0=%b, a1=%b, b0=%b, b1=%b, c0=%b, c1=%b, c2=%b, c3=%b ", $time, a0, a1,b0, b1, c0,c1,c2,c3);
    end

    stMultiplier n1(c0,c1,c2,c3,a0,a1,b0,b1);
endmodule // arith_tb