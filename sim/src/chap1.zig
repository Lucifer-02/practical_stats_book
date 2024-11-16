const std = @import("std");
const testing = std.testing;
const assert = std.debug.assert;
const expect = std.testing.expect;
const eql = std.mem.eql;

pub fn mean(comptime T: type, data: []const T) f64 {
    assert(data.len > 0); // not accept empty data

    var sum: f64 = 0;

    switch (T) {
        i16, i32, i64 => for (data) |value| {
            sum += @as(f32, @floatFromInt(value));
        },

        f16, f32, f64 => for (data) |value| {
            sum += value;
        },

        else => @compileError("Not support this type!"),
    }

    return sum / @as(f32, @floatFromInt(data.len));
}

pub fn trimmedMean(comptime T: type, data: []const T, trim: usize) f64 {
    assert(data.len > trim * 2); // the trimming not over data length

    //Make a copy
    const allocator = std.heap.page_allocator;
    const copy = allocator.dupe(T, data) catch {
        @panic("Can't make a copy");
    };
    defer allocator.free(copy);

    std.mem.sort(T, copy, {}, comptime std.sort.asc(T));

    const trimmed_data = copy[trim..(copy.len - trim)];
    assert(trimmed_data.len == (copy.len - 2 * trim));

    return mean(T, trimmed_data);
}

pub fn weightedMean(comptime T: type, data: []const T, weights: []const f16) f64 {
    assert(data.len == weights.len); // each weight must belong to a entry

    var weighted: f64 = 0;
    var sum_weights: f64 = 0;

    switch (T) {
        i16, i32, i64 => for (0..(data.len)) |i| {
            weighted += @as(f64, @floatFromInt(data[i])) * weights[i];
            sum_weights += weights[i];
        },
        f16, f32, f64 => for (0..(data.len)) |i| {
            weighted += data[i] * weights[i];
            sum_weights += weights[i];
        },

        else => @compileError("Not support this type!"),
    }

    return weighted / sum_weights;
}

pub fn median(comptime T: type, data: []const T) f64 {
    assert(data.len > 1);

    //Make a copy
    const allocator = std.heap.page_allocator;
    const copy = allocator.dupe(T, data) catch {
        @panic("Can't make a copy");
    };
    defer allocator.free(copy);

    std.mem.sort(T, copy, {}, comptime std.sort.asc(T));

    switch (T) {
        i16, i32, i64 => if (data.len % 2 == 1) {
            return @as(f64, @floatFromInt(data[data.len / 2]));
        } else {
            return @as(f64, @floatFromInt(data[(data.len / 2) - 1] + data[data.len / 2])) / 2;
        },

        f16, f32, f64 => if (data.len % 2 == 1) {
            return data[data.len / 2];
        } else {
            return (data[(data.len / 2) - 1] + data[data.len / 2]) / 2;
        },

        else => @compileError("Not support this type!"),
    }
}

test "test mean 1" {
    const data = [_]f32{ 1, 2, 3 };
    try testing.expect(mean(f32, &data) == 2);
}

test "test mean 2" {
    const data = [_]f32{ 1, 2 };
    try testing.expect(mean(f32, &data) == 1.5);
}

test "test mean 3" {
    const data = [_]i32{ 1, 2 };
    try testing.expect(mean(i32, &data) == 1.5);
}

test "test trimmed mean 1" {
    var data = [_]i32{ 0, 1, 2, 0 };
    try testing.expect(trimmedMean(i32, &data, 1) == 0.5);
}

test "test trimmed mean 2" {
    var data = [_]f16{ 0, 1.5, 2, 0 };
    try testing.expect(trimmedMean(@TypeOf(data[0]), &data, 1) == 0.75);
}

test "test trimmed mean 3" {
    var data = [_]f16{ 0, 1, 2, 1, 3 };
    try testing.expect(trimmedMean(@TypeOf(data[0]), &data, 2) == 1);
}

test "test weighted mean 1" {
    const data = [_]f16{ 2, 4 };
    const weights = [_]f16{ 0.5, 0.5 };
    try testing.expect(weightedMean(@TypeOf(data[0]), &data, &weights) == 3.0);
}

test "test weighted mean 2" {
    const data = [_]i16{ 2, 4 };
    const weights = [_]f16{ 0.5, 0.5 };
    try testing.expect(weightedMean(@TypeOf(data[0]), &data, &weights) == 3.0);
}

test "test weighted mean 3" {
    const data = [_]f32{ 2, 4 };
    const weights = [_]f16{ 0.5, 0.5 };
    try testing.expect(weightedMean(@TypeOf(data[0]), &data, &weights) == 3.0);
}
test "test median 1" {
    const data = [_]f32{ 2, 4 };
    try testing.expect(median(@TypeOf(data[0]), &data) == 3);
}
test "test median 2" {
    const data = [_]i32{ 2, 3 };
    try testing.expect(median(@TypeOf(data[0]), &data) == 2.5);
}
