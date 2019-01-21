
clear
clc
close all;
% set init data
window_size = [512, 512];
save_image_num = 10;
folder_name = 'cut_images';
% picture_name_R = '/home/david/Documents/MyResearch/MyPaper/lidaan/OSSP/xiaogongwei/testPy/R_B.tif';
% picture_name_G = '/home/david/Documents/MyResearch/MyPaper/lidaan/OSSP/xiaogongwei/testPy/G_B.tif';
% picture_name_B = '/home/david/Documents/MyResearch/MyPaper/lidaan/OSSP/xiaogongwei/testPy/B_B.tif';

% % read all image_name to image_data
% image_name = {picture_name_R, picture_name_G, picture_name_B};
% for i = 1 : numel(image_name)
%     fprintf('Will read image: %s\n', image_name{i})
%     image_data(:,:,i) = imread(image_name{i}); % use imread read image
% end
% fprintf('Sucess to you, all image have read.\n')
file_path_name = '/home/david/Documents/Github/OSSP/xiaogongwei/ManuImages/ice.jpg';
image_data = imread(file_path_name);
% rand window to cut image
[rows, cols] = size(image_data(:,:,1));
rows_max = rows - window_size(1) - 1;
cols_max = cols - window_size(2) - 1;
row_rand_array = floor(rand(1,save_image_num)*rows_max + 1);
col_rand_array = floor(rand(1,save_image_num)*rows_max + 1);
% make dir 
[image_floder, image_name] = fileparts(file_path_name);
cuts_image_floder = fullfile(image_floder, folder_name);
if ~exist(cuts_image_floder,'dir')
   mkdir(cuts_image_floder);
end
% cut images
temp_flag = rand()*10 + 1;
rand_falg = rand() * temp_flag + 1;

for n = 1 : save_image_num
    temp_image_name =[ 'image_' num2str(n) '_' num2str(rand_falg,10) '.tif' ];
    save_image_file_name = fullfile(cuts_image_floder, temp_image_name);
    row_begin = row_rand_array(n);
    col_begin = col_rand_array(n);
    row_index = row_begin : row_begin+window_size(1) - 1;
    col_index = col_begin : col_begin+window_size(2) - 1;
    cut_temp_image = image_data(row_index, col_index, :);
    imwrite(cut_temp_image, save_image_file_name);
    manualCreatMask( cut_temp_image,  save_image_file_name);
    pause(5)
%     choice = questdlg('I do not want work!!! ', 'Warning', 'Yes', 'No', 'No');
%     switch choice
%     case 'Yes'
%         break;
%     end

end
fprintf('Sucess to you, all image have cuted.\n')











