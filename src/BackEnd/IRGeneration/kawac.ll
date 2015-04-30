; ModuleID = 'Module Test'

%KawaClass_class_c = type opaque
%KawaClass_class_A = type { %KawaClass_Struct_class_A*, i8** }
%KawaClass_Struct_class_A = type { float, %KawaClass_class_A*, %KawaClass_class_b*, i8* }
%KawaClass_class_b = type opaque

@kawa_format_int = constant [3 x i8] c"%d\00"
@kawa_format_double = constant [3 x i8] c"%f\00"
@kawa_format_char = constant [3 x i8] c"%c\00"
@static_class_A_avatar = external global i32
@attribut_index__class_A_index = global i32 0
@attribut_index__class_A_bossun = global i32 1
@attribut_index__class_A_repre = global i32 2
@static_class_A_sepe = external global %KawaClass_class_c
@attribut_index__class_A_mpm = global i32 3
@static_class_A_lovea = external global double
@KAWA_FORMAT_INT_TO_STRING = external constant %KawaClass_class_A
@0 = private unnamed_addr constant [10 x i8] c"afficheOk\00"
@methode_index_afficheOk = global i32 6
@adhocTable__class_A_class_A = constant [7 x i8*] [i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*), i8* bitcast (void ()* @afficheOk to i8*)]
@abs_index = global i32 1558
@abs_indexcd = external global i32

; Function Attrs: nounwind
declare i32 @puts(i8*) #0

; Function Attrs: nounwind
declare i32 @strlen(i8*) #0

declare i8* @strcat(i8*, i8*)

define i8* @int_to_str(i32) {
entry:
  %1 = call i8* @malloc(i64 50)
  %2 = call i32 (i8*, i8*, ...)* @sprintf(i8* %1, i8* getelementptr inbounds ([3 x i8]* @kawa_format_int, i32 0, i32 0), i32 %0)
  ret i8* %1
}

; Function Attrs: nounwind
declare i8* @malloc(i64) #0

declare i32 @sprintf(i8*, i8*, ...)

define i8* @float_to_str(double) {
entry:
  %1 = call i8* @malloc(i64 50)
  %2 = call i32 (i8*, i8*, ...)* @sprintf(i8* %1, i8* getelementptr inbounds ([3 x i8]* @kawa_format_double, i32 0, i32 0), double %0)
  ret i8* %1
}

define i32 @main(i32 %argc, i8** %argv) {
entry:
  %0 = call %KawaClass_class_A* @KawaConstructor_class_A_pt_KawaVoid()
  %1 = getelementptr %KawaClass_class_A* %0, i32 0, i32 1
  %2 = load i8*** %1
  %3 = bitcast i8** %2 to void ()**
  %4 = getelementptr void ()** %3, i32 3
  %5 = load void ()** %4
  call void %5()
  ret i32 0
}

define i8* @char_to_str(i8) {
entry:
  %1 = call i8* @malloc(i64 50)
  %2 = call i32 (i8*, i8*, ...)* @sprintf(i8* %1, i8* getelementptr inbounds ([3 x i8]* @kawa_format_char, i32 0, i32 0), i8 %0)
  ret i8* %1
}

declare i8* @calloc(i64, i64)

define i8* @concat(i8*, i8*) {
  %3 = call i32 @strlen(i8* %0)
  %4 = call i32 @strlen(i8* %1)
  %5 = add i32 %3, %4
  %6 = sext i32 %5 to i64
  %7 = add i64 %6, 1
  %8 = call i8* @calloc(i64 1, i64 %7)
  %9 = call i8* @strcat(i8* %8, i8* %0)
  %10 = call i8* @strcat(i8* %9, i8* %1)
  ret i8* %10
}

define void @afficheOk() {
entry:
  %0 = call i8* @concat(i8* getelementptr inbounds ([10 x i8]* @0, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8]* @0, i32 0, i32 0))
  %1 = call i32 @puts(i8* %0)
  ret void
}

define i8** @get_table_adhocTable__class_A_class_A() {
entry:
  ret i8** getelementptr inbounds ([7 x i8*]* @adhocTable__class_A_class_A, i32 0, i32 0)
}

define %KawaClass_class_A* @KawaConstructor_class_A_pt_KawaVoid() {
entry:
  %this = alloca %KawaClass_class_A
  %0 = call i8** @get_table_adhocTable__class_A_class_A()
  %1 = getelementptr %KawaClass_class_A* %this, i32 0, i32 1
  store i8** %0, i8*** %1
  call void @SubConstructor_class_A_pt_KawaVoid(%KawaClass_class_A* %this)
  ret %KawaClass_class_A* %this
}

define void @SubConstructor_class_A_pt_KawaVoid(%KawaClass_class_A* %this) {
entry:
  ret void
}

attributes #0 = { nounwind }
