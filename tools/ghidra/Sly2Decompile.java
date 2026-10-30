// Decompile the functions listed in a CSV (Name,Start,End) into one C file per function.
// Usage (headless): -postScript Sly2Decompile.java OUTDIR LISTCSV
// @category Sly2
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.List;

public class Sly2Decompile extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args[0]);
        out.mkdirs();
        List<String> lines = Files.readAllLines(new File(args[1]).toPath(), StandardCharsets.UTF_8);
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        int done = 0, failed = 0;
        for (String line : lines) {
            if (monitor.isCancelled()) break;
            String[] p = line.trim().split(",");
            if (p.length < 2 || !p[1].startsWith("0x")) continue;
            Address a = toAddr(Long.decode(p[1]));
            Function f = getFunctionAt(a);
            if (f == null) f = createFunction(a, null);
            if (f == null) { failed++; continue; }
            DecompileResults r = decompiler.decompileFunction(f, 90, monitor);
            if (!r.decompileCompleted() || r.getDecompiledFunction() == null) { failed++; continue; }
            Files.writeString(new File(out, p[0] + ".c").toPath(), "// Ghidra decompilation of " + p[0] + " @ " + p[1] + "\n" + r.getDecompiledFunction().getC(), StandardCharsets.UTF_8);
            done++;
        }
        println("Sly2Decompile: wrote " + done + " functions, " + failed + " failed");
    }
}
