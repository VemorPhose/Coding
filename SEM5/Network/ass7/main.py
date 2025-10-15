
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

pure_aloha_df = pd.read_csv('PureAloha.csv')
pure_aloha_df.head()


frame_size = 1460 * 8  # in bits
pure_aloha_df["Bandwidth_bps"] = pure_aloha_df["Mbps"] * 1e6
pure_aloha_df["Frame_time_s"] = frame_size / pure_aloha_df["Bandwidth_bps"]

pure_aloha_df["G"] = (pure_aloha_df["Packet_transmitted"] / pure_aloha_df["Simulation_Time"]) * pure_aloha_df["Frame_time_s"]
pure_aloha_df["S"] = (pure_aloha_df["Packet_received"] / pure_aloha_df["Simulation_Time"]) * pure_aloha_df["Frame_time_s"]

pure_aloha_df.to_csv('Pure_Aloha_Processed.csv', index=False)
pure_aloha_df.head()

G_vals = np.linspace(0, 1.2, 400) 
S_pure = G_vals * np.exp(-2 * G_vals)

plt.figure(figsize=(8,5))
plt.plot(pure_aloha_df["G"], pure_aloha_df["S"], marker='o', label='Experimental S (per frame time)')
plt.plot(G_vals, S_pure, linestyle='--', label='Theoretical S (Pure ALOHA)')
plt.xlabel('Offered load G (frames/frame-time)')
plt.ylabel('Throughput S (frames/frame-time)')
plt.title('G vs Throughput S — Experimental vs Theoretical')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()


slotted_aloha_df = pd.read_csv('SlottedAloha.csv')
slotted_aloha_df.head()

frame_size = 1460 * 8  # in bits
slotted_aloha_df["Bandwidth_bps"] = slotted_aloha_df["Mbps"] * 1e6
slotted_aloha_df["Frame_time_s"] = frame_size / slotted_aloha_df["Bandwidth_bps"]

slotted_aloha_df["G"] = (slotted_aloha_df["Packet_transmitted"] / slotted_aloha_df["Simulation_Time"]) * slotted_aloha_df["Frame_time_s"]
slotted_aloha_df["S"] = (slotted_aloha_df["Packet_received"] / slotted_aloha_df["Simulation_Time"]) * slotted_aloha_df["Frame_time_s"]

slotted_aloha_df.to_csv('Slotted_Aloha_Processed.csv', index=False)
slotted_aloha_df.head()

S_slotted = G_vals * np.exp(-1 * G_vals)

plt.figure(figsize=(8,5))
plt.plot(slotted_aloha_df["G"], slotted_aloha_df["S"], marker='o', label='Experimental S (per frame time)')
plt.plot(G_vals, S_slotted, linestyle=':', label='Theoretical S (Slotted ALOHA)')
plt.xlabel('Offered load G (frames/frame-time)')
plt.ylabel('Throughput S (frames/frame-time)')
plt.title('G vs Throughput S — Experimental vs Theoretical')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

plt.figure(figsize=(8,5))
plt.plot(pure_aloha_df["G"], pure_aloha_df["S"], marker='o', label='Experimental S (Pure ALOHA)')
plt.plot(slotted_aloha_df["G"], slotted_aloha_df["S"], marker='o', label='Experimental S (Slotted ALOHA)')
plt.plot(G_vals, S_pure, linestyle='--', label='Theoretical S (Pure ALOHA)')
plt.plot(G_vals, S_slotted, linestyle=':', label='Theoretical S (Slotted ALOHA)')
plt.xlabel('Offered load G (frames/frame-time)')
plt.ylabel('Throughput S (frames/frame-time)')
plt.title('G vs Throughput S — Experimental vs Theoretical')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('G_vs_Throughput_S.png', dpi=300)
plt.show()

