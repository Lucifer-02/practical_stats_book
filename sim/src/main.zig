const std = @import("std");
const mean = @import("chap1.zig").weightedMean;

pub fn main() !void {
    const data = [_]i32{ 1, 2, 3 };
    const weights = [_]f16{ 1, 2, 3 };
    std.debug.print("Mean of {d} is {d}\n", .{ data, mean(i32, &data, &weights) });
}
