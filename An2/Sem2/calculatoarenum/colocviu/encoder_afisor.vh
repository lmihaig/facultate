// Licu Mihai-George CTI 262

//   a
// f   b
//   g   
// e   c
//   d


module seven_segment_display(a,b,c,d,e,f,g,A,B,C,D);
    input A,B,C,D;
    output wire a,b,c,d,e,f,g,h;

    assign a = (~D&B) | (C&B) | (D&~A) | (~C&~A) | (~D&C&A) | (D&~C&B);
    assign b = (~C&~B) + (~C&~A) | (~D&~B&~A) | (~D&B&A) | (D&~B&A);
    assign c = (~D&C) | (D&~C) | (~B&A) | (~D&~B) | (~D&A);
    assign d = (D&~B) | (C&B&~A) | (~C&B&A) | (~D&~C&~A) | (C&~B&A);
    assign e = (D&C) | (B&~A) | (D&B) | (D&~A) | (~C&~A);
    assign f = (D&~C) | (~B&~A) | (C&~A) | (D&B) | (~D&C&~B);
    assign g = (D&~C) | (B&~A) | (D&A) | (~C&B)|(~D&C&~B);
endmodule //seven_segment_display


module arith_tb;
    reg b0,b1,b2,b3;
    wire a,b,c,d,e,f,g;

    initial begin
        $dumpfile("encoder_afisor.vcd");
        $dumpvars;
            // 0000
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 0;

        #5
        b0 = 1; // 0001
        #5
        b0 = 0;
        b1 = 1; // 0010
        #5
        b0 = 1; // 0011
        #5
        b0 = 0;
        b1 = 0;
        b2 = 1; // 0100
        #5
        b0 = 1; // 0101
        #5
        b0 = 0;
        b1 = 1; // 0110
        #5
        b0 = 1; // 0111
        #5
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 1; // 1000
        #5
        b0 = 1; // 1001
        #5
        b0 = 0;
        b1 = 1; // 1010
        #5
        b0 = 1; // 1011
        #5
        b0 = 0;
        b1 = 0;
        b2 = 1; // 1100
        #5
        b0 = 1; // 1101
        #5
        b0 = 0;
        b1 = 1; // 1110
        #5
        b0 = 1; // 1111


        #20 $finish;  
    end

    initial begin
      $monitor ("time=%0d, b0=%b, b1=%b, b2=%b, b3=%b, a=%b, b=%b, c=%b, d=%b, e=%b, f=%b, g=%b", $time, b0,b1,b2,b3,a,b,c,d,e,f,g);
    end

    seven_segment_display n1(a,b,c,d,e,f,g,b0,b1,b2,b3);;
endmodule // arith_tb
