reg [0:7] A,B
reg C;
initial begin: stop_at
#20; $stop;
end

initial begin: Init
A=0;
$display("Time A B C");
$monitor("%0d %b %b %b", $time, A,B,C);
end

always begin: main_process
#1 A=A+1;
#1 B[0:3]=~A[4:7];
#1 C=&A[6:7];
end
endmodule