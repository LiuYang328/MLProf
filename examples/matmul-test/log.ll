; ModuleID = 'LLVMDialectModule'
source_filename = "LLVMDialectModule"

@assert_msg = private constant [46 x i8] c"Matmul does not produce same output as matvec\00"

declare void @abort()

declare void @puts(ptr)

declare void @free(ptr)

declare ptr @malloc(i64)

declare void @printMemrefF32(i64, ptr)

define { ptr, ptr, i64, [2 x i64], [2 x i64] } @matmul(ptr %0, ptr %1, i64 %2, i64 %3, i64 %4, i64 %5, i64 %6, ptr %7, ptr %8, i64 %9, i64 %10, i64 %11, i64 %12, i64 %13) {
  %15 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %7, 0
  %16 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %15, ptr %8, 1
  %17 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, i64 %9, 2
  %18 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %17, i64 %10, 3, 0
  %19 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %18, i64 %12, 4, 0
  %20 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %19, i64 %11, 3, 1
  %21 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %20, i64 %13, 4, 1
  %22 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %0, 0
  %23 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %22, ptr %1, 1
  %24 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %23, i64 %2, 2
  %25 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %24, i64 %3, 3, 0
  %26 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %25, i64 %5, 4, 0
  %27 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %26, i64 %4, 3, 1
  %28 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %27, i64 %6, 4, 1
  %29 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %30 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %29, ptr %30, align 4
  %31 = getelementptr [2 x i64], ptr %30, i32 0, i64 0
  %32 = load i64, ptr %31, align 4
  %33 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 3
  %34 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %33, ptr %34, align 4
  %35 = getelementptr [2 x i64], ptr %34, i32 0, i64 1
  %36 = load i64, ptr %35, align 4
  %37 = mul i64 %36, %32
  %38 = getelementptr float, ptr null, i64 %37
  %39 = ptrtoint ptr %38 to i64
  %40 = call ptr @malloc(i64 %39)
  %41 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %40, 0
  %42 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %41, ptr %40, 1
  %43 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %42, i64 0, 2
  %44 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %43, i64 %32, 3, 0
  %45 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %44, i64 %36, 3, 1
  %46 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %45, i64 %36, 4, 0
  %47 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %46, i64 1, 4, 1
  br label %48

48:                                               ; preds = %62, %14
  %49 = phi i64 [ %63, %62 ], [ 0, %14 ]
  %50 = icmp slt i64 %49, %32
  br i1 %50, label %51, label %64

51:                                               ; preds = %48
  br label %52

52:                                               ; preds = %55, %51
  %53 = phi i64 [ %61, %55 ], [ 0, %51 ]
  %54 = icmp slt i64 %53, %36
  br i1 %54, label %55, label %62

55:                                               ; preds = %52
  %56 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 1
  %57 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 4, 0
  %58 = mul i64 %49, %57
  %59 = add i64 %58, %53
  %60 = getelementptr float, ptr %56, i64 %59
  store float 0.000000e+00, ptr %60, align 4
  %61 = add i64 %53, 1
  br label %52

62:                                               ; preds = %52
  %63 = add i64 %49, 1
  br label %48

64:                                               ; preds = %48
  %65 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %66 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %65, ptr %66, align 4
  %67 = getelementptr [2 x i64], ptr %66, i32 0, i64 0
  %68 = load i64, ptr %67, align 4
  %69 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %70 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %69, ptr %70, align 4
  %71 = getelementptr [2 x i64], ptr %70, i32 0, i64 1
  %72 = load i64, ptr %71, align 4
  %73 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 3
  %74 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %73, ptr %74, align 4
  %75 = getelementptr [2 x i64], ptr %74, i32 0, i64 1
  %76 = load i64, ptr %75, align 4
  br label %77

77:                                               ; preds = %117, %64
  %78 = phi i64 [ %118, %117 ], [ 0, %64 ]
  %79 = icmp slt i64 %78, %68
  br i1 %79, label %80, label %119

80:                                               ; preds = %77
  br label %81

81:                                               ; preds = %115, %80
  %82 = phi i64 [ %116, %115 ], [ 0, %80 ]
  %83 = icmp slt i64 %82, %76
  br i1 %83, label %84, label %117

84:                                               ; preds = %81
  br label %85

85:                                               ; preds = %88, %84
  %86 = phi i64 [ %114, %88 ], [ 0, %84 ]
  %87 = icmp slt i64 %86, %72
  br i1 %87, label %88, label %115

88:                                               ; preds = %85
  %89 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 1
  %90 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 4, 0
  %91 = mul i64 %78, %90
  %92 = add i64 %91, %86
  %93 = getelementptr float, ptr %89, i64 %92
  %94 = load float, ptr %93, align 4
  %95 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 1
  %96 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 4, 0
  %97 = mul i64 %86, %96
  %98 = add i64 %97, %82
  %99 = getelementptr float, ptr %95, i64 %98
  %100 = load float, ptr %99, align 4
  %101 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 1
  %102 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 4, 0
  %103 = mul i64 %78, %102
  %104 = add i64 %103, %82
  %105 = getelementptr float, ptr %101, i64 %104
  %106 = load float, ptr %105, align 4
  %107 = fmul float %94, %100
  %108 = fadd float %106, %107
  %109 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 1
  %110 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, 4, 0
  %111 = mul i64 %78, %110
  %112 = add i64 %111, %82
  %113 = getelementptr float, ptr %109, i64 %112
  store float %108, ptr %113, align 4
  %114 = add i64 %86, 1
  br label %85

115:                                              ; preds = %85
  %116 = add i64 %82, 1
  br label %81

117:                                              ; preds = %81
  %118 = add i64 %78, 1
  br label %77

119:                                              ; preds = %77
  ret { ptr, ptr, i64, [2 x i64], [2 x i64] } %47
}

define { ptr, ptr, i64, [2 x i64], [2 x i64] } @matvec(ptr %0, ptr %1, i64 %2, i64 %3, i64 %4, i64 %5, i64 %6, ptr %7, ptr %8, i64 %9, i64 %10, i64 %11, i64 %12, i64 %13) {
  %15 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %7, 0
  %16 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %15, ptr %8, 1
  %17 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, i64 %9, 2
  %18 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %17, i64 %10, 3, 0
  %19 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %18, i64 %12, 4, 0
  %20 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %19, i64 %11, 3, 1
  %21 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %20, i64 %13, 4, 1
  %22 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %0, 0
  %23 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %22, ptr %1, 1
  %24 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %23, i64 %2, 2
  %25 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %24, i64 %3, 3, 0
  %26 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %25, i64 %5, 4, 0
  %27 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %26, i64 %4, 3, 1
  %28 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %27, i64 %6, 4, 1
  %29 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %30 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %29, ptr %30, align 4
  %31 = getelementptr [2 x i64], ptr %30, i32 0, i64 0
  %32 = load i64, ptr %31, align 4
  %33 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %34 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %33, ptr %34, align 4
  %35 = getelementptr [2 x i64], ptr %34, i32 0, i64 1
  %36 = load i64, ptr %35, align 4
  %37 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 3
  %38 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %37, ptr %38, align 4
  %39 = getelementptr [2 x i64], ptr %38, i32 0, i64 1
  %40 = load i64, ptr %39, align 4
  %41 = mul i64 %40, %32
  %42 = getelementptr float, ptr null, i64 %41
  %43 = ptrtoint ptr %42 to i64
  %44 = call ptr @malloc(i64 %43)
  %45 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %44, 0
  %46 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %45, ptr %44, 1
  %47 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %46, i64 0, 2
  %48 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %47, i64 %32, 3, 0
  %49 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %48, i64 %40, 3, 1
  %50 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %49, i64 %40, 4, 0
  %51 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %50, i64 1, 4, 1
  br label %52

52:                                               ; preds = %66, %14
  %53 = phi i64 [ %67, %66 ], [ 0, %14 ]
  %54 = icmp slt i64 %53, %32
  br i1 %54, label %55, label %68

55:                                               ; preds = %52
  br label %56

56:                                               ; preds = %59, %55
  %57 = phi i64 [ %65, %59 ], [ 0, %55 ]
  %58 = icmp slt i64 %57, %40
  br i1 %58, label %59, label %66

59:                                               ; preds = %56
  %60 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %51, 1
  %61 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %51, 4, 0
  %62 = mul i64 %53, %61
  %63 = add i64 %62, %57
  %64 = getelementptr float, ptr %60, i64 %63
  store float 0.000000e+00, ptr %64, align 4
  %65 = add i64 %57, 1
  br label %56

66:                                               ; preds = %56
  %67 = add i64 %53, 1
  br label %52

68:                                               ; preds = %52
  br label %69

69:                                               ; preds = %144, %68
  %70 = phi i64 [ %145, %144 ], [ 0, %68 ]
  %71 = icmp slt i64 %70, %40
  br i1 %71, label %72, label %146

72:                                               ; preds = %69
  %73 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 0
  %74 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 1
  %75 = insertvalue { ptr, ptr, i64 } undef, ptr %73, 0
  %76 = insertvalue { ptr, ptr, i64 } %75, ptr %74, 1
  %77 = insertvalue { ptr, ptr, i64 } %76, i64 0, 2
  %78 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 2
  %79 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 3, 0
  %80 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 3, 1
  %81 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 4, 0
  %82 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %21, 4, 1
  %83 = extractvalue { ptr, ptr, i64 } %77, 0
  %84 = extractvalue { ptr, ptr, i64 } %77, 1
  %85 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } undef, ptr %83, 0
  %86 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %85, ptr %84, 1
  %87 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %86, i64 %70, 2
  %88 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %87, i64 %36, 3, 0
  %89 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %88, i64 %81, 4, 0
  %90 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %51, 0
  %91 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %51, 1
  %92 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } undef, ptr %90, 0
  %93 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %92, ptr %91, 1
  %94 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %93, i64 %70, 2
  %95 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %94, i64 %32, 3, 0
  %96 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %95, i64 %40, 4, 0
  %97 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %98 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %97, ptr %98, align 4
  %99 = getelementptr [2 x i64], ptr %98, i32 0, i64 0
  %100 = load i64, ptr %99, align 4
  %101 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 3
  %102 = alloca [2 x i64], i64 1, align 8
  store [2 x i64] %101, ptr %102, align 4
  %103 = getelementptr [2 x i64], ptr %102, i32 0, i64 1
  %104 = load i64, ptr %103, align 4
  br label %105

105:                                              ; preds = %142, %72
  %106 = phi i64 [ %143, %142 ], [ 0, %72 ]
  %107 = icmp slt i64 %106, %100
  br i1 %107, label %108, label %144

108:                                              ; preds = %105
  br label %109

109:                                              ; preds = %112, %108
  %110 = phi i64 [ %141, %112 ], [ 0, %108 ]
  %111 = icmp slt i64 %110, %104
  br i1 %111, label %112, label %142

112:                                              ; preds = %109
  %113 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 1
  %114 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %28, 4, 0
  %115 = mul i64 %106, %114
  %116 = add i64 %115, %110
  %117 = getelementptr float, ptr %113, i64 %116
  %118 = load float, ptr %117, align 4
  %119 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %89, 1
  %120 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %89, 2
  %121 = getelementptr float, ptr %119, i64 %120
  %122 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %89, 4, 0
  %123 = mul i64 %110, %122
  %124 = getelementptr float, ptr %121, i64 %123
  %125 = load float, ptr %124, align 4
  %126 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 1
  %127 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 2
  %128 = getelementptr float, ptr %126, i64 %127
  %129 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 4, 0
  %130 = mul i64 %106, %129
  %131 = getelementptr float, ptr %128, i64 %130
  %132 = load float, ptr %131, align 4
  %133 = fmul float %118, %125
  %134 = fadd float %132, %133
  %135 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 1
  %136 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 2
  %137 = getelementptr float, ptr %135, i64 %136
  %138 = extractvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %96, 4, 0
  %139 = mul i64 %106, %138
  %140 = getelementptr float, ptr %137, i64 %139
  store float %134, ptr %140, align 4
  %141 = add i64 %110, 1
  br label %109

142:                                              ; preds = %109
  %143 = add i64 %106, 1
  br label %105

144:                                              ; preds = %105
  %145 = add i64 %70, 1
  br label %69

146:                                              ; preds = %69
  ret { ptr, ptr, i64, [2 x i64], [2 x i64] } %51
}

define void @main() {
  %1 = call ptr @malloc(i64 ptrtoint (ptr getelementptr (float, ptr null, i64 15) to i64))
  %2 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %1, 0
  %3 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %2, ptr %1, 1
  %4 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %3, i64 0, 2
  %5 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %4, i64 5, 3, 0
  %6 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %5, i64 3, 3, 1
  %7 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %6, i64 3, 4, 0
  %8 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %7, i64 1, 4, 1
  %9 = call ptr @malloc(i64 ptrtoint (ptr getelementptr (float, ptr null, i64 6) to i64))
  %10 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } undef, ptr %9, 0
  %11 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %10, ptr %9, 1
  %12 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %11, i64 0, 2
  %13 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %12, i64 3, 3, 0
  %14 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %13, i64 2, 3, 1
  %15 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %14, i64 2, 4, 0
  %16 = insertvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %15, i64 1, 4, 1
  br label %17

17:                                               ; preds = %31, %0
  %18 = phi i64 [ %32, %31 ], [ 0, %0 ]
  %19 = icmp slt i64 %18, 5
  br i1 %19, label %20, label %33

20:                                               ; preds = %17
  br label %21

21:                                               ; preds = %24, %20
  %22 = phi i64 [ %30, %24 ], [ 0, %20 ]
  %23 = icmp slt i64 %22, 3
  br i1 %23, label %24, label %31

24:                                               ; preds = %21
  %25 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 1
  %26 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 4, 0
  %27 = mul i64 %18, %26
  %28 = add i64 %27, %22
  %29 = getelementptr float, ptr %25, i64 %28
  store float 1.300000e+01, ptr %29, align 4
  %30 = add i64 %22, 1
  br label %21

31:                                               ; preds = %21
  %32 = add i64 %18, 1
  br label %17

33:                                               ; preds = %17
  br label %34

34:                                               ; preds = %48, %33
  %35 = phi i64 [ %49, %48 ], [ 0, %33 ]
  %36 = icmp slt i64 %35, 3
  br i1 %36, label %37, label %50

37:                                               ; preds = %34
  br label %38

38:                                               ; preds = %41, %37
  %39 = phi i64 [ %47, %41 ], [ 0, %37 ]
  %40 = icmp slt i64 %39, 2
  br i1 %40, label %41, label %48

41:                                               ; preds = %38
  %42 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 1
  %43 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 0
  %44 = mul i64 %35, %43
  %45 = add i64 %44, %39
  %46 = getelementptr float, ptr %42, i64 %45
  store float 1.700000e+01, ptr %46, align 4
  %47 = add i64 %39, 1
  br label %38

48:                                               ; preds = %38
  %49 = add i64 %35, 1
  br label %34

50:                                               ; preds = %34
  %51 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 1
  %52 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 0
  %53 = mul i64 0, %52
  %54 = add i64 %53, 0
  %55 = getelementptr float, ptr %51, i64 %54
  store float 1.300000e+01, ptr %55, align 4
  %56 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 0
  %57 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 1
  %58 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 2
  %59 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 3, 0
  %60 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 3, 1
  %61 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 4, 0
  %62 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 4, 1
  %63 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 0
  %64 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 1
  %65 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 2
  %66 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 3, 0
  %67 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 3, 1
  %68 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 0
  %69 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 1
  %70 = call { ptr, ptr, i64, [2 x i64], [2 x i64] } @matmul(ptr %56, ptr %57, i64 %58, i64 %59, i64 %60, i64 %61, i64 %62, ptr %63, ptr %64, i64 %65, i64 %66, i64 %67, i64 %68, i64 %69)
  %71 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 0
  %72 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 1
  %73 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 2
  %74 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 3, 0
  %75 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 3, 1
  %76 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 4, 0
  %77 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %8, 4, 1
  %78 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 0
  %79 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 1
  %80 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 2
  %81 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 3, 0
  %82 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 3, 1
  %83 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 0
  %84 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %16, 4, 1
  %85 = call { ptr, ptr, i64, [2 x i64], [2 x i64] } @matvec(ptr %71, ptr %72, i64 %73, i64 %74, i64 %75, i64 %76, i64 %77, ptr %78, ptr %79, i64 %80, i64 %81, i64 %82, i64 %83, i64 %84)
  br label %86

86:                                               ; preds = %109, %50
  %87 = phi i64 [ %110, %109 ], [ 0, %50 ]
  %88 = icmp slt i64 %87, 5
  br i1 %88, label %89, label %111

89:                                               ; preds = %86
  br label %90

90:                                               ; preds = %107, %89
  %91 = phi i64 [ %108, %107 ], [ 0, %89 ]
  %92 = icmp slt i64 %91, 2
  br i1 %92, label %93, label %109

93:                                               ; preds = %90
  %94 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %70, 1
  %95 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %70, 4, 0
  %96 = mul i64 %87, %95
  %97 = add i64 %96, %91
  %98 = getelementptr float, ptr %94, i64 %97
  %99 = load float, ptr %98, align 4
  %100 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %85, 1
  %101 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %85, 4, 0
  %102 = mul i64 %87, %101
  %103 = add i64 %102, %91
  %104 = getelementptr float, ptr %100, i64 %103
  %105 = load float, ptr %104, align 4
  %106 = fcmp oeq float %99, %105
  br i1 %106, label %107, label %118

107:                                              ; preds = %93
  %108 = add i64 %91, 1
  br label %90

109:                                              ; preds = %90
  %110 = add i64 %87, 1
  br label %86

111:                                              ; preds = %86
  %112 = alloca { ptr, ptr, i64, [2 x i64], [2 x i64] }, i64 1, align 8
  store { ptr, ptr, i64, [2 x i64], [2 x i64] } %85, ptr %112, align 8
  %113 = insertvalue { i64, ptr } { i64 2, ptr undef }, ptr %112, 1
  %114 = extractvalue { i64, ptr } %113, 0
  %115 = extractvalue { i64, ptr } %113, 1
  call void @printMemrefF32(i64 %114, ptr %115)
  %116 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %70, 0
  call void @free(ptr %116)
  %117 = extractvalue { ptr, ptr, i64, [2 x i64], [2 x i64] } %85, 0
  call void @free(ptr %117)
  ret void

118:                                              ; preds = %93
  call void @puts(ptr @assert_msg)
  call void @abort()
  unreachable
}

!llvm.module.flags = !{!0}

!0 = !{i32 2, !"Debug Info Version", i32 3}
