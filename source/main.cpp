/*  ThemeSwitch is a homebrew for Nintendo Switch to change between themes.
    Copyright (C) <2019>  <Ángel Luis Perales Gómez>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <switch.h>

void copy_dir(const char *src,const char *dest);
void install_theme(char*);
int remove_dir(const char *path);
unsigned char detect_cfw();
int row= 2;
void copy_dir2();

char installed_theme[] = "sdmc://themes/installed_theme.txt";
char cfw[25];
char selected_theme[100];

unsigned char detect_cfw(){
    if( access( "sdmc://atmosphere", F_OK ) != -1 ) {
        sprintf(cfw, "atmosphere");
        return 0;
    }else if( access( "sdmc://reinx", F_OK ) != -1 ) {
        sprintf(cfw, "reinx");
        return 0;
    }if( access( "sdmc://sxos", F_OK ) != -1 ) {
        sprintf(cfw, "sxos");
        return 0;
    }
    return 255;
}

void install_theme(char* new_theme){
    /*printf("\x1b[5;28HInstalling theme");
    char buffer[100], installed_theme[255];
    sprintf(buffer, "sdmc://%s/titles/", cfw);
    sprintf(installed_theme, "%s/0100000000001000", buffer);
    if( access( installed_theme, F_OK ) != -1 ) {
        printf("\x1b[5;30HRemoving %s...", installed_theme);
        remove_dir(installed_theme);
        mkdir(installed_theme, 0777);
        printf("\x1b[6;30HInstalling %s...", new_theme);
        copy_dir(new_theme, buffer);
    } else {
        printf("\x1b[6;30HInstalling %s...", new_theme);
        mkdir(installed_theme, 0777);
        copy_dir(new_theme, buffer);
    }*/
    copy_dir2();
}

void copy_files(char* src_buf, char* dst_buf){
    FILE *fd_src = fopen(src_buf, "r");
    FILE *fd_dst = fopen(dst_buf, "w");
    unsigned char read_buffer[512];
    int ret;
    //printf("\x1b[%d;30Hcopying %s into %s...", row, buf, dst_buf);
    //row += 3;
    while ((ret = fread(read_buffer, 1, 512, fd_src))==512){
        fwrite(read_buffer, 1, 512, fd_dst);
    }
    if (ret != 512){
        fwrite(read_buffer, 1, ret, fd_dst);
    }
    fclose(fd_src);
    fclose(fd_dst);
}

void copy_dir2(){
    char buffer[512], dst_buffer[512];
    sprintf(buffer, "sdmc://%s/titles/0100000000001000", cfw);
    mkdir(buffer,0777);
    sprintf(buffer, "sdmc://%s/titles/0100000000001000/exefs", cfw);
    mkdir(buffer,0777);
    sprintf(buffer, "sdmc://%s/titles/0100000000001000/romfs", cfw);
    mkdir(buffer,0777);
    // copy files
    sprintf(buffer, "sdmc://themes/%s/0100000000001000/fsmitm.flag", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/fsmitm.flag", cfw);
    copy_files(buffer, dst_buffer);
    //exefs
    sprintf(buffer, "sdmc://themes/%s/0100000000001000/exefs/main", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/exefs/main", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/exefs/main.npdm", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/exefs/main.npdm", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/exefs/rtld", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/exefs/rtld", cfw);
    copy_files(buffer, dst_buffer);

    // romfs

    sprintf(buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt", cfw);
    mkdir(buffer,0777);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/common.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/common.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Entrance.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Entrance.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Eula.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Eula.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Flaunch.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Flaunch.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Gift.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Gift.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Interrupt.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Interrupt.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Migration.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Migration.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Notification.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Notification.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Option.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Option.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/ResidentMenu.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/ResidentMenu.szs", cfw);
    copy_files(buffer, dst_buffer);

    sprintf(buffer, "sdmc://themes/%s/0100000000001000/romfs/lyt/Set.szs", selected_theme);
    sprintf(dst_buffer, "sdmc://%s/titles/0100000000001000/romfs/lyt/Set.szs", cfw);
    copy_files(buffer, dst_buffer);

    printf("\x1b[30;5Hfinished!");
}

void copy_dir(const char *source_path, const char *destination_path){
    printf("\x1b[%d;30Hcopying %s into %s...", row, source_path, destination_path);
    row += 3;
   DIR *d = opendir(source_path);
   size_t path_len = strlen(source_path);
   size_t dst_path_len = strlen(destination_path);

   if (!d){
    printf("\x1b[5;30HCould not open %s...", source_path);
   }

   if (d){
      struct dirent *p;
      while ((p=readdir(d))){
          char *buf, *dst_buf;
          size_t len;

          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = (char*)malloc(len);
          len = dst_path_len + strlen(p->d_name) + 2; 
          dst_buf = (char*)malloc(len);

          if (buf){
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", source_path, p->d_name);
             sprintf(dst_buf, "%s/%s", destination_path, p->d_name);
             if (!stat(buf, &statbuf)){
                if (S_ISDIR(statbuf.st_mode)){
                    mkdir(dst_buf,0777);
                    printf("\x1b[%d;30HCreating dir %s...", row, dst_buf);
                    row += 3;
                    copy_dir(buf, dst_buf);
                }
                else{
                    FILE *fd_src = fopen(buf, "r");
                    FILE *fd_dst = fopen(dst_buf, "w");
                    unsigned char read_buffer[512];
                    int ret;
                    printf("\x1b[%d;30Hcopying %s into %s...", row, buf, dst_buf);
                    row += 3;
                    while ((ret = fread(read_buffer, 1, 512, fd_src))==512){
                        fwrite(read_buffer, 1, 512, fd_dst);
                    }
                    if (ret != 512){
                        fwrite(read_buffer, 1, ret, fd_dst);
                    }
                    fclose(fd_src);
                    fclose(fd_dst);
                }
             }
             free(buf);
             free(dst_buf);
          }
      }
      closedir(d);
   }
}

int remove_dir(const char *path){
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d){
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d))){
          int r2 = -1;
          char *buf;
          size_t len;

          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = (char*)malloc(len);

          if (buf){
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)){
                if (S_ISDIR(statbuf.st_mode)){
                   r2 = remove_dir(buf);
                }
                else{
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r){
      r = rmdir(path);
   }
   return r;
}

void print_menu(std::vector<std::string> themes, long unsigned int pointed){

    printf("\x1b[10;5HSelect a theme to install");

    for (long unsigned int i = 0 ; i < themes.size(); i++){
        if (i == pointed){
            printf("\x1b[%d;5H->%s (%d)",(int)(11+i), themes.at(i).c_str(), (int)i);
        }else{
            printf("\x1b[%d;5H                                                        ", (int)(11+i));
            printf("\x1b[%d;5H%s  (%d)",(int)(11+i), themes.at(i).c_str(), (int)i);
        }
        
    }
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);
    std::vector<std::string> themes;

    DIR* dir;
    struct dirent* ent;
    char path[] = "sdmc://themes";
    dir = opendir(path);
    detect_cfw();
    if(dir==NULL)
    {
        printf("\x1b[5;5HFailed to open dir. themes folder doesn't exist in the sd root");
    }
    else
    {
        printf("\x1b[29;5HReading themes from SD...");
        int a= 30;
        while ((ent = readdir(dir)))
        {
            themes.push_back(ent->d_name);
            a+=1;
        }
        closedir(dir);
    }
    long unsigned int pointed = 0;
    print_menu(themes, pointed);

    while (appletMainLoop())
    {
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;
        else if (kDown & KEY_DDOWN){
            pointed = (pointed + 1) % themes.size();
            print_menu(themes, pointed);
        }else if (kDown & KEY_DUP){
            pointed = (pointed - 1);
            if (pointed < 0){
                pointed = themes.size()-1;
            }
            print_menu(themes, pointed);
        }else if (kDown & KEY_A){
            char new_theme[255];
            sprintf(selected_theme, "%s", themes.at(pointed).c_str());
            sprintf(new_theme, "%s/%s/0100000000001000", path, themes.at(pointed).c_str());
            install_theme(new_theme);
        }
        consoleUpdate(NULL);
    }
    consoleExit(NULL);
    return 0;
}
