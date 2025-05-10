; ModuleID = 'hello.cpp'
source_filename = "hello.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.anon = type { i8 }

@__const.main.lam = private unnamed_addr constant %class.anon undef, align 1

; Function Attrs: mustprogress noinline norecurse optnone uwtable
define dso_local noundef i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca %class.anon, align 1
  store i32 0, ptr %1, align 4
    #dbg_declare(ptr %2, !15, !DIExpression(), !23)
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %2, ptr align 1 @__const.main.lam, i64 1, i1 false), !dbg !23
  %3 = call noundef i32 @"_ZZ4mainENK3$_0clEv"(ptr noundef nonnull align 1 dereferenceable(1) %2), !dbg !24
  ret i32 %3, !dbg !25
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define internal noundef i32 @"_ZZ4mainENK3$_0clEv"(ptr noundef nonnull align 1 dereferenceable(1) %0) #2 align 2 !dbg !26 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
    #dbg_declare(ptr %2, !27, !DIExpression(), !29)
  %3 = load ptr, ptr %2, align 8
  ret i32 42, !dbg !30
}

attributes #0 = { mustprogress noinline norecurse optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.linker.options = !{}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "hello.cpp", directory: "/home/klb/Temp/demo/llvm-ir", checksumkind: CSK_MD5, checksum: "ca608ab7233c91b70e0287e93ae5acdf")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)"}
!10 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !11, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !{}
!15 = !DILocalVariable(name: "lam", scope: !10, file: !1, line: 3, type: !16)
!16 = distinct !DICompositeType(tag: DW_TAG_class_type, scope: !10, file: !1, line: 3, size: 8, flags: DIFlagTypePassByValue, elements: !17)
!17 = !{!18}
!18 = !DISubprogram(name: "operator()", scope: !16, file: !1, line: 3, type: !19, scopeLine: 3, flags: DIFlagPublic | DIFlagPrototyped, spFlags: DISPFlagLocalToUnit)
!19 = !DISubroutineType(types: !20)
!20 = !{!13, !21}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, flags: DIFlagArtificial | DIFlagObjectPointer)
!22 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!23 = !DILocation(line: 3, column: 10, scope: !10)
!24 = !DILocation(line: 4, column: 12, scope: !10)
!25 = !DILocation(line: 4, column: 5, scope: !10)
!26 = distinct !DISubprogram(name: "operator()", linkageName: "_ZZ4mainENK3$_0clEv", scope: !16, file: !1, line: 3, type: !19, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, declaration: !18, retainedNodes: !14)
!27 = !DILocalVariable(name: "this", arg: 1, scope: !26, type: !28, flags: DIFlagArtificial | DIFlagObjectPointer)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64)
!29 = !DILocation(line: 0, scope: !26)
!30 = !DILocation(line: 3, column: 30, scope: !26)
