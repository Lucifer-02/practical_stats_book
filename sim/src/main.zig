const std = @import("std");
const mean = @import("chap1.zig").mean;

pub fn main() !void {
    const data = [_]i32{ 1, 2 };
    std.debug.print("Mean of {d} is {d}\n", .{ data, mean(i32, &data) });
}
